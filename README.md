# libentropy
shannon entropy 

# install

```
$ make
cc -std=c11 -Wall -fPIC -O2 -DNDEBUG  -I./include -c src/entropy.c -o src/entropy.o
cc -shared -std=c11 -Wall -fPIC -O2 -DNDEBUG -o libentropy.so src/entropy.o
cc -std=c11 -Wall -fPIC -O2 -DNDEBUG  -I./include src/main.c -o entropy libentropy.so -lm
$ sudo make install
install -Dm644 include/entropy.h /usr/include/entropy/entropy.h
install -Dm644 libentropy.so /usr/lib/
install -Dm755 entropy /usr/bin/
$ ldd entropy
linux-vdso.so.1 (0x00007ffe163f6000)
libentropy.so => /usr/lib/libentropy.so (0x00007f1b186e8000)
libm.so.6 => /usr/lib/libm.so.6 (0x00007f1b183ea000)
libc.so.6 => /usr/lib/libc.so.6 (0x00007f1b18046000)
/lib64/ld-linux-x86-64.so.2 (0x00007f1b188e9000)
$
```

# example
```
$ echo 'abc' | entropy
<stdin>: 2.000000
$ echo 'abcdef' | entropy
<stdin>: 2.807355
$ find /usr/bin -size +5M | xargs entropy | column -t
/usr/bin/gdb:                    5.794477
/usr/bin/cephfs-table-tool:      6.441336
/usr/bin/mongosniff:             6.307009
/usr/bin/ceph-syn:               6.467057
/usr/bin/perf:                   5.606387
/usr/bin/mongoperf:              6.306273
/usr/bin/gs:                     2.838588
/usr/bin/phantomjs:              6.500455
/usr/bin/fleetd:                 5.006788
/usr/bin/mongos:                 6.254940
/usr/bin/etcd:                   5.510529
/usr/bin/ceph-dencoder:          6.454515
/usr/bin/haxe:                   5.557423
/usr/bin/ceph-mds:               6.439570
/usr/bin/cluster:                2.272601
/usr/bin/ssh-chat:               5.119294
/usr/bin/docker:                 5.459386
/usr/bin/ceph-fuse:              6.463146
/usr/bin/godoc:                  5.436795
/usr/bin/gvmap:                  2.274877
/usr/bin/dub:                    6.211901
/usr/bin/ceph-objectstore-tool:  6.492676
/usr/bin/clang-3.7:              6.411015
/usr/bin/ceph-mon:               6.462703
/usr/bin/ctest:                  6.391732
/usr/bin/crystal:                6.320560
/usr/bin/mongod:                 6.305930
/usr/bin/arm-none-eabi-gdb:      6.335348
/usr/bin/clang-check:            6.323003
/usr/bin/node:                   6.575414
/usr/bin/cephfs-journal-tool:    6.440483
/usr/bin/edgepaint:              2.222340
/usr/bin/cargo:                  5.947786
/usr/bin/emacs-24.5:             4.100438
/usr/bin/mongo:                  6.327808
/usr/bin/lldb-server-3.7.0:      6.363826
/usr/bin/qemu-system-i386:       5.291281
/usr/bin/qemu-system-x86_64:     5.295855
/usr/bin/trace:                  5.606387
/usr/bin/go:                     5.336115
/usr/bin/ceph-osd:               6.489573
$
$ find /usr/bin -size +10M | xargs entropy | awk -F : '{if ($2 < 5) print $0}' | column -t
/usr/bin/gs:          2.838588
/usr/bin/cluster:     2.272601
/usr/bin/gvmap:       2.274877
/usr/bin/edgepaint:   2.222340
/usr/bin/emacs-24.5:  4.100438
$
$ cp /usr/bin/cluster .
$ xz -vk cluster
cluster (1/1)
  100 %        343.8 KiB / 19.4 MiB = 0.017   989 KiB/s       0:20
$ entropy cluster cluster.xz
cluster: 2.272601
cluster.xz: 7.999520
$ ls -lh cluster cluster.xz
-rwxr-xr-x 1 sharow wheel  20M Dec  3 13:40 cluster
-rwxr-xr-x 1 sharow wheel 344K Dec  3 13:40 cluster.xz
$
```

# about shannon entropy
- [Entropy (information theory) - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Entropy_(information_theory))

