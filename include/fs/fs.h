typedef struct device_t
{
	int type; //0 - not used, 1 - initrd... остальное хуй его знает, потом посмотрим
	int id;
} device_t;

typedef struct fs_t
{
	int block_size;
	int type;
	device_t* dev;
} fs_t;

typedef struct handles_t
{
	char* 	(*read) 	(char* filename, int *, int *, void *, fs_t*);
	int 	(*get_size)	(char* filename, void* buffer, fs_t*);
	int 	(*exists) 	(char* filename, fs_t* );
	int 	(*is_dir)  	(char* filename, fs_t*);
} handles_t;

typedef struct mountpoint_t
{
	char *path;
	fs_t* fs;
	handles_t* handles;
} mountpoint_t;

void 	fs_init	(void);
int 	fs_mount 	(device_t *dev, handles_t *handles, int type, int id, int block_size, char* path);

int 	fs_read 	(char* filename, int start, int end, void* buffer);
int 	fs_get_size 	(char* filename, void* buffer);
int 	fs_exists	(char* filename);
int	fs_is_dir	(char* filename);

//int	fs_files_list	(char* dir);
//int	fs_mount_list	(void);

mountpoint_t **fs_mountpoints; 	// это не просто указатель на указатель, это массив с данными 
					// о точках монтирования
int mounts_count;
