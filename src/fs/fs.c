#include <fs/fs.h>
#include <string.h>
#include <memory.h>

void fs_init(void)
{
	fs_mountpoints = (mountpoint_t **) malloc ( sizeof(mountpoint_t) * 228 ); // 228 ничего не значит, я просто
										  // выделяю побольше памяти
	mounts_count = 0;
}

int fs_mount (device_t *dev, handles_t *handles, int type, int id, int block_size, char* path)
{
	mountpoint_t *new_mount = (mountpoint_t *) malloc ( sizeof(mountpoint_t)); //выделяем память под временные
										  //данные о новом монтировании
	for (int i; i < mounts_count; i++)
		if (strcmp(fs_mountpoints[i]->path, path) == 0)
			return 0; 	// уже примонтировано. втос не разрешает (пока) 
					// монтировать более 1 фс в одну директорию
	
	
	//ну тут все понятно, добавляем данные 
	new_mount->fs = (fs_t *) malloc (sizeof (fs_t *));
	new_mount->fs->block_size 	= block_size;
	new_mount->fs->type 		= type;
	new_mount->fs->dev 		= dev;
	
	new_mount->path		= path;
	new_mount->handles 		= handles;
	
	fs_mountpoints[mounts_count++] = new_mount;
	free (new_mount);
	return 1;
}

int fs_find(char* path, int *filename_add)
{
	char* a = (char*)malloc(strlen(path) + 1);
	memset(a, 0, strlen(path) + 1);
	memcpy(a, path, strlen(path) + 1);
	
	int at = 0;
	if(a[strlen(a)] == '/') str_bksp(a, '/');
	while(1)
	{
		for(int i = 0; i < 228; ++i)
		{
			if(!fs_mountpoints[i])
				break;
			if(strcmp(fs_mountpoints[i]->path, a) == 0)
			{
				*filename_add = strlen(a) - 1;
				free(a);
				return i;
			}
		}
		if(strcmp(a, "/") == 0)
			break;
		str_bksp(a, '/');
	}
	return 0;
}

int fs_read (char* filename, int start, int end, void* buffer)
{
	int x = 0;
	int mount_number = fs_find(filename, &x);
	filename += x + 1;
	
	if (fs_mountpoints[mount_number]->handles->read == 0) //если такая операция не поддерживается
		return 0; 
		
	return fs_mountpoints[mount_number]->handles->read(filename, start, end, buffer, fs_mountpoints[mount_number]->fs);
}

int fs_get_size (char* filename, void* buffer)
{
	int x = 0;
	int mount_number = fs_find(filename, &x);
	filename += x + 1;
	
	if (fs_mountpoints[mount_number]->handles->get_size == 0) //если такая операция не поддерживается
		return 0; 
		
	return fs_mountpoints[mount_number]->handles->get_size(filename, buffer, fs_mountpoints[mount_number]->fs);
}

int fs_exists (char* filename)
{
	int x = 0;
	int mount_number = fs_find(filename, &x);
	filename += x + 1;
	
	if (fs_mountpoints[mount_number]->handles->exists == 0) //если такая операция не поддерживается
		return 0; 
		
	return fs_mountpoints[mount_number]->handles->exists(filename, fs_mountpoints[mount_number]->fs);
}

int fs_is_dir (char* filename)
{
	int x = 0;
	int mount_number = fs_find(filename, &x);
	filename += x + 1;
	
	if (fs_mountpoints[mount_number]->handles->is_dir == 0) //если такая операция не поддерживается
		return 0; 
		
	return fs_mountpoints[mount_number]->handles->is_dir(filename, fs_mountpoints[mount_number]->fs);
}
