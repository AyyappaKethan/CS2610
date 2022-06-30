%include "io.mac"

section .data
  output_file_name db "input.txt"
  struc_mmap:
    .addr: dd 0
    .len: dd 4096
    .prot: dd 1h
    .flags: dd 2h
    .fd: dd -1
    .off: dd 0  ;struct created for mmap contains arguments
  out_child db "Child Output:" ,0
  out_parent db "Parent Output:" ,0

section .bss
  n resd 1  ; number of elements
  fd_out  resd 1  ;file descriptor
  inp resb 11  ;buffer for storing input
  fptr resd 1  ;storing pointer returned mmap memory mapped
  arr resd 4096 ;storing array
  fork resb 1  ;storing fork

section .text
global _start
_start:
  mov eax,8
	mov ebx,output_file_name
	mov ecx,777o
	int 0x80
	mov [fd_out],eax   ;creating a file
   
	GetLInt eax
	mov [n],eax
  push eax           ;taking input of number of elements 

  repeat_read: 
    pop eax
    cmp eax,0
    je after_read
    dec eax
    push eax
    
    mov eax,3
    mov ebx,0
    mov ecx,inp
    mov edx,11
    int 0x80       ;taking input from keyboard read string is stored in inp(buffer)
    
    dec eax
    mov edi,inp
    mov BL,0
    mov [edi+eax],BL
    inc eax        ;appending null charecter
    
    mov edx,eax
    mov eax,4
    mov ebx,[fd_out]
    mov ecx,inp
    int 0x80       ;writing from input buffer to file

    jmp repeat_read

  after_read:
    mov eax,6
    mov ebx,[fd_out]
    int 0x80                  ;closing the file

    mov eax,5
    mov ebx, output_file_name
    mov ecx,2
    mov edx,777o
    int 0x80
    mov [struc_mmap.fd],eax  ;opening the file

    mov ebx,struc_mmap
    mov eax,90
	  int 0x80              ;using mmap to map into the memory
    
    mov [fptr], eax
    mov eax,0
    push eax
    mov eax,0
    mov edx,0             ;storing mapped memory start pointer fptr

  start:
    mov ecx,[fptr]
    mov ebx,0
    mov bl,[ecx+eax]
    cmp bl,0
    je for
    imul edx,10
    sub ebx,48
    add edx,ebx
    inc eax
    jmp start              ;creating the integer from string
 
  for:
    pop ecx
    push eax
    mov eax,arr
    mov [eax+4*ecx],edx
    pop eax
    inc eax
    inc ecx
    push ecx
    cmp ecx,[n]
    je nxtnxt
    mov edx,0
    jmp start            ;storing the integer in array

  nxtnxt:
   mov eax,2
   int 0x80
   mov [fork],eax        ;calling system call fork and storing the value of eax in fork

  child:
   mov eax,arr           ; moving array starting address to eax
   mov ecx,[n]           
   xor edx,edx           
   sub ecx,1             ;made edx=0,ecx=n-1 where n is total number of integers

  nxt:
    cmp ecx,0
    jl end_prog
    mov ebx,[eax+4*ecx]
    add edx,ebx
    sub ecx,1
    jmp nxt           ;adding every element in array to edx once

  end_prog:
    mov eax,[fork]
    cmp eax,0
    jg parent        ;if the process has a value of fork(eax)>1 then it will jump to parent process or else it'll print the sum and end the process

    PutStr out_child
    nwln
    PutLInt edx
    nwln
    mov eax,1
    int 0x80         ;printing the sum and ending the child proccess

  parent:            ;only parent process can access this part of code(from here on)
    mov ecx,[n]
    mov ebx,1
    mov eax, arr     

  for_loop:                  ;starting a for loop to sort
    cmp ebx,[n]
    jge print_loop           ;jumps to printing section when the sorting is done
    push ebx                 ;storing the no of iteration i 
    mov edx,[eax+4*ebx]      ;stroring the value of key in edx
    dec ebx

  while_loop:                ;starting a while loop to find the proper index to store key with iterator j
    cmp ebx,0
    jge cond                 

  end_while:                 ;directly goes to end of while if 1st condition is wrong
    inc ebx
    mov [eax+4*ebx],edx
    pop ebx
    inc ebx
    jmp for_loop             ;place the value of key in the array location corresponding to the iterator where it stops after searching for a location to place the key in while loop and jumps to for loop

  print_loop:  
    mov eax,arr
    mov ebx,0

    mov ecx,1000000
    delay:
    loop delay             ;to delay the parent output so that it won't get mixed up with child output

    PutStr out_parent
    nwln

  print:
    mov ecx,[eax+4*ebx]
    PutLInt ecx
    nwln
    inc ebx
    cmp ebx,[n]
    je end
    jmp print             ;prints the sorted array
  
  end:
    mov eax,1
    int 0x80              ;ends the parent process
     
  cond:
    cmp [eax+4*ebx],edx
    jg while_impl        ;enters the while loop if it satisfies both the conditions: the iterator j reaches 0 and the value corresponding to iterator in array is grater than key
    jmp end_while        ; if second condition is wwrong jmp to end of while

  while_impl:
    mov edi,ebx
    add ebx,1
    mov ecx,[eax+4*edi]
    mov [eax+4*ebx],ecx
    sub ebx,1
    sub ebx,1
    jmp while_loop        ; in the implementation of while we will send the value of array corresponding to j to address of array corresponding to j+1 creating a slot to keep out key in a[j] if(a[j-1]<=key)

  

  
  

 


     

     
     

     
 
   
   




	
