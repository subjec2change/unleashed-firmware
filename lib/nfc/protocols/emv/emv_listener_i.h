#pragma once

#include <nfc/protocols/nfc_generic_event.h>

#include "emv_listener.h"

#ifdef __cplusplus
extern "C" {
#endif

struct EmvListener {
    Iso14443_4aListener* iso14443_4a_listener;
    EmvData* data;

    NfcGenericEvent generic_event;
    EmvListenerEvent emv_event;
    EmvListenerEventData emv_event_data;
    NfcGenericCallback callback;
    void* context;
};

#ifdef __cplusplus
}
#endif
