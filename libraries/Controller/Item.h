#ifndef _ITEM_H_
#define _ITEM_H_

#define itemKey(key) (String("'") + String(key) + String("':"))
#define itemKeyNext(key) (String(", '") + String(key) + String("':"))
#define itemRange(start, end) (String("[") + String(start) + "," + String(end) + "]")
#define itemString(val) (String("'") + String(val) + String("'"))
#define itemNext(key, value) (itemKeyNext(key) + String(value))
#define itemNew(key, value) (itemKey(key) + String(value))

typedef String item_t;

static inline String itemInfo(String type, int mode, String range, float freq)
{
	String info = "{'type':'" + type + "', 'mode':" + String(mode);
	
	if (range.length() > 0)
		info +=  ", 'range':{" + range + "}";
	if (freq > 0)
		info += ", 'freq':" + String(freq);
	
	return info + "}";
}

static inline int itemCopy(item_t &item, char *buf, size_t size)
{
	item.toCharArray(buf, size);
	return item.length();
}

#endif
