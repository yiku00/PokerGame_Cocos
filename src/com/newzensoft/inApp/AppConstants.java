package com.newzensoft.inApp;

import androidx.annotation.StringDef;

import com.gaa.sdk.iap.PurchaseClient.ProductType;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class AppConstants {
    private AppConstants() {
        throw new IllegalAccessError("Utility class");
    }

    @StringDef({
            InappType.PRODUCT_INAPP_5500,
            InappType.PRODUCT_INAPP_11000,
            InappType.PRODUCT_INAPP_22000,
            InappType.PRODUCT_INAPP_55000,
            InappType.PRODUCT_INAPP_99000
    })
    @Retention(RetentionPolicy.SOURCE)
    public @interface InappType {
        String PRODUCT_INAPP_5500 = "ruby_01";  // 소모성 상품코드 (10 coins) - 10,000원권 아이템
        String PRODUCT_INAPP_11000 = "ruby_02";  // 소모성 상품코드 (One more item) - 50,000원권 아이템
        String PRODUCT_INAPP_22000 = "ruby_03";
        String PRODUCT_INAPP_55000 = "ruby_04";
        String PRODUCT_INAPP_99000 = "ruby_05";
    }

    @StringDef({
        AutoType.PRODUCT_INAPP_3300
    })
    @Retention(RetentionPolicy.SOURCE)
    public @interface AutoType {
        String PRODUCT_INAPP_3300 = "m_ruby_01"; // 월정액 상품코드
    }

    private static final String[] IN_APP_PRODUCTS = {InappType.PRODUCT_INAPP_5500, InappType.PRODUCT_INAPP_11000, InappType.PRODUCT_INAPP_22000, InappType.PRODUCT_INAPP_55000, InappType.PRODUCT_INAPP_99000};
    private static final String[] AUTO_PRODUCTS = {AutoType.PRODUCT_INAPP_3300};

    public static List<String> getProductList(@ProductType String productType) {
        return new ArrayList<String>(Arrays.asList(ProductType.INAPP.equals(productType) ? IN_APP_PRODUCTS : AUTO_PRODUCTS));
    }

    public static List<String> getAllProductList() {
        List<String> result = getProductList(ProductType.INAPP);
        result.addAll(getProductList(ProductType.AUTO));
        return result;
    }

    // Lucky ONE Shared Preference Key
    public static final String KEY_MODE_MONTHLY = "MODE_MONTHLY";
    public static final String KEY_ONE_MORE = "ONE_MORE";
    public static final String KEY_TOTAL_COIN = "TOTAL_COIN";
    public static final String KEY_PAYLOAD = "PAYLOAD";
    public static final String KEY_IS_FIRST = "IS_FIRST";
    public static final String KEY_STORE_CODE = "STORE_CODE";

}
