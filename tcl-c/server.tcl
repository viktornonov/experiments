proc Serve {chan addr port} {
  fconfigure $chan -translation auto -buffering line
  set request [gets $chan]
  puts "Channel - $chan"
  puts "Request - $request"
  set path [file join . [string trimleft [lindex $request 1] /]]
  puts "Trying to open $path"
  if { [catch {
      set fl [open $path]
  } err] } {
    puts "Not Found"
    puts $chan "HTTP/1.1 404 Not Found"
    puts $chan "Content-Type: text/html"
    puts $chan ""
    puts $chan "No one is home"
  } else {
    puts $chan "HTTP/1.1 200 OK"
    puts $chan "Content-Type: text/html"
    puts $chan ""
    puts $chan [read $fl]
    close $fl
  }
  close $chan
}

set sk [socket -server Serve 5151]
vwait forever
