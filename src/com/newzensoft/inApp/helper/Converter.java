package com.numixent.inApp.helper;

import com.numixent.inApp.pdu.CommandRequest;
import com.numixent.inApp.pdu.Response;
import com.numixent.inApp.pdu.VerifyReceipt;

public interface Converter {
    public String toJson(final CommandRequest r);

    public Response fromJson(final String json);

    public VerifyReceipt fromJson2VerifyReceipt(final String json);
}
