ARQ=$1
termux-x11 :1 &
cp -rf $CASA/pacotes/Ycaro/biblioteca .
cd biblioteca
clang $ARQ.c -o $ARQ -lSDL2
./$ARQ
rm $ARQ
