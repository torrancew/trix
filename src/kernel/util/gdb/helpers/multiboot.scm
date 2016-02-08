(use-modules
  (gdb)
  (gdb types)
  (gdb iterator)
  (gdb printing))

(define (make-multiboot-struct-tostring value)
  (lambda (printer)
    (format #f "~a<0x~8,'0x>"
            (type-name (value-type value))
            (value->integer (value-address value)))))

(define (make-multiboot-struct-iterator value)
  (lambda (printer)
    (make-list-iterator
      (map
        (lambda (field)
          (cons (field-name  field) (value-field value (field-name field))))
        (type-fields (value-type value))))))

(define (make-multiboot-struct-printer value)
  "Print multiboot structs"
  (make-pretty-printer-worker
    "map"
    (make-multiboot-struct-tostring value)
    (make-multiboot-struct-iterator value)))

(define (multiboot-struct-lookup-fn pp val)
  (let ((type (value-type val)))
    (and (or (= TYPE_CODE_STRUCT (type-code type))
             (and (= TYPE_CODE_TYPEDEF (type-code type))
                  (= TYPE_CODE_STRUCT  (type-code (type-target type)))))
         (string-prefix? "multiboot_" (type-name type))
         (make-multiboot-struct-printer val))))

(append-pretty-printer! #f
                        (make-pretty-printer "multiboot-struct-printer"
                                             multiboot-struct-lookup-fn))
