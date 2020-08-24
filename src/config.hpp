#ifndef CONFIG_HPP
#define CONFIG_HPP

enum Gen{Artin,Dual};
#define STRANDS 4
#define MAXLEN 32
<<<<<<< HEAD
#define DATA_DIR string("/home/fromentin/data/") //string("/workdir/lmpa/jfromentin/")
=======
#define DATA_DIR string("data/") //string("/workdir/lmpa/jfromentin/")
>>>>>>> e1c2d0179e8933165b0bfb4e90f20ec19575cf66
#define GEN Artin
#define SERVER_IP "127.0.0.1" //"192.168.1.3" //Orval 02
#define SERVER_PORT 5555
#define MAX_MSG_SIZE 1024
#define MAX_CLIENTS 1024
#define MAX_WORKERS 800
#endif
