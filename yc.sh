ARQ=$1
# mata qualquer instancia anterior
pkill -f termux-x11 2>/dev/null
# inicia uma nova
termux-x11 :1 &
sleep 2
cp -rf $CASA/pacotes/Ycaro/biblioteca .
cd biblioteca
clang $ARQ.c -o $ARQ -lSDL2
DISPLAY=:1 ./$ARQ
rm $ARQ
