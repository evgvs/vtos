shutdown:
  movw $0x1000,%ax
  movw %ss,%ax
  movw $0xf000,%sp
  movw $0x5307,%ax
  movw $0x0001,%bx
  movw $0x0003,%cx
  int $0x15

  ret
