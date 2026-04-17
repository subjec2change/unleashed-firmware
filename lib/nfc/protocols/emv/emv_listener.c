#include "emv_listener_i.h"

#include <furi.h>
#include <nfc/protocols/nfc_listener_base.h>

#define TAG "EmvListener"

static EmvListener* emv_listener_alloc(Iso14443_4aListener* iso14443_4a_listener, EmvData* data) {
    furi_assert(iso14443_4a_listener);

    EmvListener* instance = malloc(sizeof(EmvListener));
    instance->iso14443_4a_listener = iso14443_4a_listener;
    instance->data = data;

    instance->emv_event.data = &instance->emv_event_data;
    instance->generic_event.protocol = NfcProtocolEmv;
    instance->generic_event.instance = instance;
    instance->generic_event.event_data = &instance->emv_event;

    return instance;
}

static void emv_listener_free(EmvListener* instance) {
    furi_assert(instance);

    free(instance);
}

static void emv_listener_set_callback(
    EmvListener* instance,
    NfcGenericCallback callback,
    void* context) {
    furi_assert(instance);

    instance->callback = callback;
    instance->context = context;
}

static const EmvData* emv_listener_get_data(EmvListener* instance) {
    furi_assert(instance);
    furi_assert(instance->data);

    return instance->data;
}

static NfcCommand emv_listener_run(NfcGenericEvent event, void* context) {
    furi_assert(context);
    furi_assert(event.protocol == NfcProtocolIso14443_4a);
    furi_assert(event.event_data);

    EmvListener* instance = context;
    Iso14443_4aListenerEvent* iso14443_4a_event = event.event_data;
    NfcCommand command = NfcCommandContinue;

    if(iso14443_4a_event->type == Iso14443_4aListenerEventTypeFieldOff) {
        instance->emv_event.type = EmvListenerEventTypeFieldOff;
        if(instance->callback) {
            command = instance->callback(instance->generic_event, instance->context);
        }
    }

    return command;
}

const NfcListenerBase nfc_listener_emv = {
    .alloc = (NfcListenerAlloc)emv_listener_alloc,
    .free = (NfcListenerFree)emv_listener_free,
    .set_callback = (NfcListenerSetCallback)emv_listener_set_callback,
    .get_data = (NfcListenerGetData)emv_listener_get_data,
    .run = (NfcListenerRun)emv_listener_run,
};
