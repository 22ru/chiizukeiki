#!/usr/bin/expect -f
# script from https://gist.github.com/RamonGilabert/046727b302b4d9fb0055
set prompt "#"
set address [lindex $argv 0]

spawn bluetoothctl
expect -re $prompt
send "remove $address\r"
sleep 1
expect -re $prompt
send "scan on\r"
send_user "\nSleeping...\r"
sleep 5
send_user "\nDone sleeping.\r"
send "trust $address\r"
sleep 2
send "pair $address\r"
sleep 2
send "scan off\r"
send "connect $address\r"
sleep 5
send "quit\r"
expect eof