#pragma once

#include <lib/nfc/protocols/iso14443_4a/iso14443_4a_listener.h>

#include "emv.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EmvListener EmvListener;

typedef enum {
    EmvListenerEventTypeFieldOff,
} EmvListenerEventType;

typedef struct {
    BitBuffer* buffer;
} EmvListenerEventData;

typedef struct {
    EmvListenerEventType type;
    EmvListenerEventData* data;
} EmvListenerEvent;

#ifdef __cplusplus
}
#endif
