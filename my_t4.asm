#New Test #4 for assembler.
#Contains many syntax errors.
                  .text
#The text segment has multiply defined and undefined symbols. 
aa:               add     $1,$2,$3
                  j       bb
                  jj      dddd
aa:               sub     $2,$3,$4
                  jaa     eeeee
bbb:              mul     $20,$21,$22
                  jne     $20,$21,dd
                  jal     dddd
bbb:              rdr     $25
cccc:             prh     $25
                  jgt     $25,$21,ee
                  lwb     $25,0($24)
cccc:             lwa     $5,ff
                  mod     $1,$2,$3
xxxx:             lwb     $4,-1($5)
xxxx:             swb     $3,0($4)
                  j       gg
                  hlt
#Data segment begins here.
                  .data
dddd:             .resw   4
eeeee:            .word   17:2
ffffff:           .word   44:10
