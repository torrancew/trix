(use-modules
  (gdb)
  (rnrs bytevectors))

(define (send-str sock str)
  (let* ((msg  (string->utf8 str))
         (size (send sock msg)))
    (usleep 700)
    size))

(define (recv-str sock max-size)
  (let* ((buf (make-bytevector max-size 0))
         (rsz (recv! sock buf))
         (rsp (make-bytevector rsz 0)))
    (bytevector-copy! buf 0 rsp 0 rsz)
    (utf8->string rsp)))

(define (trim-cmd-output cmd out)
  (string-drop-right out (+ 1
                            (string-length "(qemu)"))))

(define qemu-state
  (make-hash-table 2))

(define qemu
  (socket PF_UNIX SOCK_STREAM 0))

(define (qemu-connect self args from-tty)
  dont-repeat
  (let ((addr (or (getenv "QEMU_SOCKET") "qemu.sock"))
        (buf  (make-bytevector 256 0)))
    (connect qemu AF_UNIX addr)
    (recv! qemu buf)
    (hashq-set! qemu-state "connected" "true")
    (hashq-set! qemu-state "address" addr)))

(define (qemu-disconnect self args from-tty)
  dont-repeat
  (shutdown qemu 1)
  (hashq-set! qemu-state "connected" "false")
  (hashq-set! qemu-state "address" "<none>"))

(define (qemu-cmd self args from-tty)
  (let ((cmd (string-append args "\n"))
        (max (* 1024 12)))
    (send-str qemu cmd)
    (display (trim-cmd-output cmd
                              (recv-str qemu max)))))

(define (qemu-status self args from-tty)
  (display "QEMU Connection Status:")
  (newline)
  (hash-fold (lambda (key val prior)
               (display (string-append "  " key ": " val))
               (newline))
             0
             qemu-state))

(register-command!
  (make-command "qemu"
                #:prefix? #t
                #:doc "Interact with a QEMU monitor socket"
                #:command-class COMMAND_STATUS
                #:invoke qemu-cmd))

(register-command!
  (make-command "qemu cmd"
                #:doc "Interact with a QEMU monitor socket"
                #:command-class COMMAND_STATUS
                #:invoke qemu-cmd))

(register-command!
  (make-command "qemu connect"
                #:doc "Connect to a QEMU monitor socket"
                #:command-class COMMAND_STATUS
                #:invoke qemu-connect))

(register-command!
  (make-command "qemu disconnect"
                #:doc "Disconnect from a QEMU monitor socket"
                #:command-class COMMAND_STATUS
                #:invoke qemu-disconnect))

(register-command!
  (make-command "qemu status"
                #:doc "Retrieve the status of the QEMU monitor socket connection"
                #:command-class COMMAND_STATUS
                #:invoke qemu-status))

