// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./bin/valgrind-out.txt ./bin/memory_leaks_debugging

int main()
{
    int *pInt = new int[10];

    return 0;
}

// ==1093== Memcheck, a memory error detector
// ==1093== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
// ==1093== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
// ==1093== Command: /home/workspace/a.out
// ==1093== Parent PID: 1065
// ==1093== 
// ==1093== 
// ==1093== HEAP SUMMARY:
// ==1093==     in use at exit: 72,744 bytes in 2 blocks
// ==1093==   total heap usage: 2 allocs, 0 frees, 72,744 bytes allocated
// ==1093== 
// ==1093== 40 bytes in 1 blocks are definitely lost in loss record 1 of 2
// ==1093==    at 0x4C2E80F: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==1093==    by 0x4005B8: main (in /workspace/home/a.out)
// ==1093== 
// ==1093== 72,704 bytes in 1 blocks are still reachable in loss record 2 of 2
// ==1093==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==1093==    by 0x4EDC365: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
// ==1093==    by 0x40106F9: call_init.part.0 (dl-init.c:72)
// ==1093==    by 0x401080A: call_init (dl-init.c:30)
// ==1093==    by 0x401080A: _dl_init (dl-init.c:120)
// ==1093==    by 0x4000C69: ??? (in /lib/x86_64-linux-gnu/ld-2.23.so)
// ==1093== 
// ==1093== LEAK SUMMARY:
// ==1093==    definitely lost: 40 bytes in 1 blocks
// ==1093==    indirectly lost: 0 bytes in 0 blocks
// ==1093==      possibly lost: 0 bytes in 0 blocks
// ==1093==    still reachable: 72,704 bytes in 1 blocks
// ==1093==         suppressed: 0 bytes in 0 blocks
// ==1093== 
// ==1093== For counts of detected and suppressed errors, rerun with: -v
// ==1093== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)