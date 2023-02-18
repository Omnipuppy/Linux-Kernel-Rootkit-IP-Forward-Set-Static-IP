# Linux-Kernel-Rootkit-IP-Forward-Set-Static-IP
ChatGPT created rootkit which allows setting a static ip and ip forwarding from kernel

sudo apt-get install linux-headers-$(uname -r)

gcc -o ip_forwarding.o -c ip_forwarding.c -I /lib/modules/$(uname -r)/build/include

make -C /lib/modules/$(uname -r)/build M=$(pwd) modules

sudo insmod ip_forwarding.ko static_ip=192.168.1.200

SET DESIRED IP TO STATIC IP OBJECT
