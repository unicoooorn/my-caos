    .global rop
rop:
    push $str2
    push $(1 + f1)
    push $str1
    push $(1 + f1)
    ret