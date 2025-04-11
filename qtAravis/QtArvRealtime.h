// QtArvRealtime.h - Realtime thread priority utilities
#pragma once

namespace QtArvRealtime {

	bool makeThreadRealtime(int priority);
	bool makeThreadHighPriority(int niceLevel);

} // namespace QtArvRealtime