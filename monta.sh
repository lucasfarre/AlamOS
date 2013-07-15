#!/bin/bash
echo "Compilando el TPE de Arqui..."
./compila
echo "Compilado."
cd ./img
echo "Montando imagen del diskette..."
sudo mount -o loop tpe.img /mnt
echo "Imagen del diskette montada con exito."
cd ..
cd ./bin
echo "Copiando el kernel a la imagen recien montada..."
sudo cp kernel.bin /mnt/boot
echo "Kernel copiado con exito."
echo "Desmontando la imagen del diskette"
sudo umount /mnt
echo "Iniciando Virtual Box..."
VBoxManage startvm AlamOS --type gui
