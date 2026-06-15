TAREFA=$1
# mata qualquer instancia anterior
pkill -f termux-x11 2>/dev/null
# inicia uma nova
termux-x11 :1 &
sleep 2
cp -rf $CASA/pacotes/Ycaro/biblioteca .
cd biblioteca
make $TAREFA
DISPLAY=:1