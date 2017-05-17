#New Test case 1 for assembler. 

               .text
test1:         lwa    $1,val01      #Puts -1 in $1.
               prh    $1

val12:         lwa    $2,val02
               prh    $2
               srl    $3,$2,16
               prh    $3

val123:        sll    $4,$1,16
               prh    $4

val1234:       srl    $5,$1,16
               prh    $5

#A label with 8 characters.
val12345:      and    $6,$1,$2
               prh    $6
               swb    $7,0($1)
               prh    $7
               hlt

               .data
val01:         .word  -1:4
val02:         .word  65535:1

#No more lines.
