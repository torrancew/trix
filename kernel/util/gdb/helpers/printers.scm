(use-modules
  (gdb)
  (gdb types)
  (gdb iterator)
  (gdb printing))

(define (make-struct-tostring value)
  (lambda (printer)
    (format #f "~a<0x~8,'0x>"
            (type-name (value-type value))
            (value->integer (value-address value)))))

(define (make-struct-iterator value)
  (lambda (printer)
    (make-list-iterator
      (map
        (lambda (field)
          (cons (field-name  field) (value-field value (field-name field))))
        (type-fields (value-type value))))))

(define (make-struct-printer value)
  "Print multiboot structs"
  (make-pretty-printer-worker
    "map"
    (make-struct-tostring value)
    (make-struct-iterator value)))

(define (struct-lookup-fn pp val)
  (let ((type (value-type val)))
    (and (or (= TYPE_CODE_STRUCT (type-code type))
             (and (= TYPE_CODE_TYPEDEF (type-code type))
                  (= TYPE_CODE_STRUCT  (type-code (type-target type)))))
         (string-prefix? "multiboot_" (type-name type))
         (make-struct-printer val))))

(append-pretty-printer! #f
                        (make-pretty-printer "struct-printer"
                                             struct-lookup-fn))
