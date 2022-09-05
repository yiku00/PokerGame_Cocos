package com.numixent.inApp.helper;

import com.google.gson.Gson;
import com.numixent.inApp.pdu.CommandRequest;
import com.numixent.inApp.pdu.Response;
import com.numixent.inApp.pdu.VerifyReceipt;

public class GsonConverter implements Converter {
	private final Gson mGson = new Gson();
	
	@Override
	public String toJson(CommandRequest r) {
		return mGson.toJson(r);
	}

	@Override
	public Response fromJson(String json) {		
		return mGson.fromJson(json, Response.class);
	}

    @Override
    public VerifyReceipt fromJson2VerifyReceipt(String json) { 
        return mGson.fromJson(json, VerifyReceipt.class);
    }

}
