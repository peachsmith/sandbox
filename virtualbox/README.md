# VirtualBox Notes

### Add user to sudoers file
```
usermod -a -G sudo <username>
```

<br/>

### Installing VirtualBox Guest Additions

First, insert the guest additions CD from the VirtualBox menu
```
sudo mount /dev/cdrom /media/cdrom
sudo /media/cdrom/./VBoxLinuxAdditions.run
```

<br/>

### Shared Folder on Windows Host

Create the folder on the host.
<br/>
Under `Machine > Settings > Shared Folders`, give Virtual Box access to the host folder.
<br/>

On the guest:

```
sudo mount -t vboxsf <shared_folder_name> <guest_os_folder_name>
```

Example:
```
sudo mount -t vboxsf debian ~/shared
```
