@ECHO OFF
echo "start hifive-vp"
echo %1
docker exec -it hifive1 hifive-vp --debug-mode %1
pause