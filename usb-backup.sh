#!/bin/bash
#author: jparlett

# This script can be used to backup a target folder to a external drive
# it is not comprehensive in options it is meant to be a hard coded solution

#uuid of ssd/hdd used for backups
uuid=""

# location to mount the backup disk
mountPnt="/mnt"

# folder you would like to back up
homeFolder="/home/<username>"

# folder you would like to your backups. Path should be relative to the location you mount the backup disk
backupsFolderRoot="/mnt/<backup folder>/"

# locate backup disk with blkid
backupDisk=$(echo $(sudo blkid --uuid $uuid))

# check for disk
if [[ $backupDisk == '' ]]; then echo "Error: Target disk not found."; exit 1; fi


# check if disk is mounted and if not attempt to mount
if [[ ! $(lsblk $backupDisk | awk ' FNR==2 { print $NF }') == $mountPnt ]];
then sudo mount $backupDisk $mountPnt && echo "Status: mounted disk at $mountPnt" || (echo "Error: could not mount disk."; exit 1)
else
  echo "Status: Disk already mounted continuing."
fi

# ensure back folder exist and move to it
if [[ -d $backupsFolderRoot ]]; 
  then cd $backupsFolderRoot 
  else echo "Error: backups folder not found"; exit 1 
fi


# store backups going back five weeks
week=1


# files should be stored in format of week-#
while read filename
do
  echo "current dir: $(pwd)"
  echo $filename
  if [[ "$filename" =~ ^week-[1-4]$ ]] 
    then ((week++))
  else
    echo "Error: invalid files in dir"
    exit 1
  fi
  echo $filename
done < <(ls)

# if weeks greater than 5 then delete oldest backup and rename folders new backup will then be week 5
echo $(ls)
# we already know files names have no spaces since we checked everything in the previous while so for loop is ok
if [[ $week -gt 4 ]]
then 
  echo "Status: reached max backups. Deleting oldest."
  week=4
  sudo rm -r "week-1"
  i=1
  echo $(ls)
  for f in $(ls)
  do
    sudo mv $f "week-$i"
    ((i++))
  done
fi

echo "next backup should be: week-$week"

# we've done all the checking now lets makes the backup
targetBackUpFolder="week-$week"
echo "Status: Making backup of $homeFolder to $backupsFolderRoot$targetBackUpFolder"

# make the new directory
sudo mkdir $targetBackUpFolder

# make backup
sudo rsync -raPz "$homeFolder" "$backupsFolderRoot$targetBackUpFolder"

# clean up
echo "Status: backup finished. Cleaning up."

# move out of directory so we can unmount it
cd /
sudo umount $backupDisk
echo "Status: unmounted disk script completed successfully"
exit 0








