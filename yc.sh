TAREFA=$1
cp yc.sh $CASA/pacotes/ycaro
# mata qualquer instancia anterior
pkill -f termux-x11 2>/dev/null
# inicia uma nova
termux-x11 :1 &
sleep 2
cp -rf $CASA/pacotes/ycaro/kit-ycaro .
cd kit-ycaro
make $TAREFA
DISPLAY=:1
