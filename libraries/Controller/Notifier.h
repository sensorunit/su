#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

#define enableNotifier() do { \
	if (_notifier) \
		_notifier->open(); \
} while (0)

#define disableNotifier() do { \
	if (_notifier) \
		_notifier->close(); \
} while (0)

#define setNotifier(notifier) do {_notifier = notifier;} while (0)

class Device;
extern Device *_notifier;

#endif
