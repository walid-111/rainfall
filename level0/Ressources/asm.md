# Prologue (pas important)
0x08048ec0 <+0>:   push   %ebp
0x08048ec1 <+1>:   mov    %esp,%ebp
0x08048ec3 <+3>:   and    $0xfffffff0,%esp
0x08048ec6 <+6>:   sub    $0x20,%esp


# Récup argv[1]
0x08048ec9 <+9>:   mov    0xc(%ebp),%eax     ; eax = argv
0x08048ecc <+12>:  add    $0x4,%eax          ; adresse de argv[1]
0x08048ecf <+15>:  mov    (%eax),%eax        ; valeur de argv[1]
0x08048ed1 <+17>:  mov    %eax,(%esp)        ; argument = argv[1]
0x08048ed4 <+20>:  call   atoi

# Comparaison
0x08048ed9 <+25>:  cmp    $0x1a7,%eax        ; compare le résultat à 0x1a7
0x08048ede <+30>:  jne    main+152           ; différent -> jump au else

# préparer /bin/sh
0x08048ee0 <+32>:  movl   $0x80c5348,(%esp)  ; adresse contenant "/bin/sh"
0x08048ee7 <+39>:  call   strdup             ; strdup("/bin/sh")
0x08048eec <+44>:  mov    %eax,0x10(%esp)    ; args[0] = shell
0x08048ef0 <+48>:  movl   $0x0,0x14(%esp)    ; args[1] = NULL

# récup les ids actuels (getegid et geteuid et non pas getgid et getuid car sinon ils retourneraient level0 et pas level1)
0x08048ef8 <+56>:  call   getegid
0x08048efd <+61>:  mov    %eax,0x1c(%esp)    ; gid = getegid()
0x08048f01 <+65>:  call   geteuid
0x08048f06 <+70>:  mov    %eax,0x18(%esp)    ; uid = geteuid()

# verrouiller les droits + lancer le shell
0x08048f0a à 0x08048f1e : copie 3x la valeur de gid sur la pile (3 arguments)
0x08048f21 <+97>:  call   setresgid          ; setresgid(gid, gid, gid)

0x08048f26 à 0x08048f3a : copie 3x la valeur de uid sur la pile (3 arguments)
0x08048f3d <+125>: call   setresuid          ; setresuid(uid, uid, uid)

0x08048f42 <+130>: lea    0x10(%esp),%eax    ; adresse du tableau args[]
0x08048f46 <+134>: mov    %eax,0x4(%esp)     ; 2e argument execv
0x08048f4a <+138>: movl   $0x80c5348,(%esp)  ; 1er argument execv = "/bin/sh"
0x08048f51 <+145>: call   execv              ; execv(shell, args)
0x08048f56 <+150>: jmp    main+192           ; saute par-dessus le else


# Else : message d'erreur
0x08048f58 <+152>: mov    0x80ee170,%eax     ; charge stdout (variable globale)
0x08048f5d <+157>: mov    %eax,%edx
0x08048f5f <+159>: mov    $0x80c5350,%eax    ; adresse de la string "No !\n"
0x08048f64 <+164>: mov    %edx,0xc(%esp)     ; argument 4 = stdout
0x08048f68 <+168>: movl   $0x5,0x8(%esp)     ; argument 3 = taille (5 = "No !\n")
0x08048f70 <+176>: movl   $0x1,0x4(%esp)     ; argument 2 = nombre d'éléments
0x08048f78 <+184>: mov    %eax,(%esp)        ; argument 1 = la string "No !\n"
0x08048f7b <+187>: call   fwrite

# Retour de la fonction
0x08048f80 <+192>: mov    $0x0,%eax
0x08048f85 <+197>: leave
0x08048f86 <+198>: ret