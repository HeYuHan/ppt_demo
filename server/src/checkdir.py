import os,sys
import platform
def create_dir(path):
	if(not os.path.exists(path)):
		print 'create dir:' + path
		os.mkdir(path)
if __name__=="__main__":
	platform_str = platform.system()
	sys_path_0 = sys.path[0]
	set_path = ""
	root_path = ""
	if(platform_str == "Windows"):
		set_path = os.popen('cd').read().replace('\n','')
	else:

		set_path = os.popen('pwd').read().replace('\n','')
	print 'config path:' + set_path
	find_str = '/server'
	if(platform_str == "Windows"):
		find_str = '\\server'
	index = set_path.index(find_str)
	root_path = set_path[0:(index+len(find_str))]

	create_dir(os.path.join(root_path,'src','lib'))
	create_dir(os.path.join(root_path,'src','bin'))

	if(root_path == sys_path_0):
		exit(0)

	if(set_path == os.path.join(root_path,'src')):
		create_dir(os.path.join(set_path,'objs'))
		exit(0)
	else:
		filter_map=['bin','lib','objs','3rd']
		create_dir(os.path.join(set_path,'objs'))
		dir_list=os.listdir(set_path);
		for dir in dir_list:
			if(not os.path.isfile(os.path.join(set_path,dir))):
				if((dir not in filter_map)):
					create_dir(os.path.join(set_path,'objs',dir))