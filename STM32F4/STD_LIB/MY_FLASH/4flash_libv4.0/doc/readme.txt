my_flash_lib

修改日期：2020/05/12

函数功能：实现数据名称以及数据值的点对点对应存储   默认存储10组数据 最大只能存储16组数据  一组数据8*2bit

数据格式：ABCDEFGH12345678

主要函数：
			void flash_save_data(uint8_t *key_name,uint8_t *val,uint8_t size)
			key_name为写入的数据名称	最大8个字符
			val为写入的数据内容	    最大8个字符
			size				必修为GROUP_SIZE	最大为15个，超过会出错
			
			uint8_t flash_get_data(uint8_t *key,uint8_t *val,uint8_t size)
			key_name为要读的数据名称	最大8个字符
			val为对应名称的数据内容	    最大8个字符
			size				必修为GROUP_SIZE	最大为15个，超过会出错
			返回结果表示是否搜索到

扇区地址：默认为第二扇区，可修改

存储的数据格式：ABCDEFGH12345678
				前8个表示名字，后8个是数据


v4.0  ： 修改了扇区而已