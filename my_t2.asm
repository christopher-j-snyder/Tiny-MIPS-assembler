#New Test 2.

           .text
p1:        add       $0,$1,$2
           sub       $3,$4,$5
           mul       $6,$7,$8
           jal       p3
           div       $9,$10,$11
           jeq       $9,$10,p1
p2:        mod       $12,$13,$14
           move      $15,$16
           jgt       $15,$16,p1
           and       $17,$18,$19
           jeq       $15,$16,p2
           jgt       $15,$16,p3
           or        $20,$21,$22
           xor       $23,$24,$25
           jne       $15,$16,p2
           com       $26,$27
p3:        sll       $28,$29,10
           srl       $30,$31,7
           jgt       $5,$6,p3
           sra       $30,$31,31
           lwa       $31,sym1
           jal       p2
           swa       $31,sym2
           j         sym1
           jeq       $15,$12,sym2

           .data
sym1:      .word     -2:5
sym2:      .resw     4
