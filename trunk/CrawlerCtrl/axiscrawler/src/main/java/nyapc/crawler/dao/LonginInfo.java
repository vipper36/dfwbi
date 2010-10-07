/**
 * LonginInfo.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.4 Apr 22, 2006 (06:55:48 PDT) WSDL2Java emitter.
 */

package nyapc.crawler.dao;

public class LonginInfo  implements java.io.Serializable {
    private java.lang.String logName;

    private java.lang.String logPass;

    private java.lang.String logUrl;

    public LonginInfo() {
    }

    public LonginInfo(
           java.lang.String logName,
           java.lang.String logPass,
           java.lang.String logUrl) {
           this.logName = logName;
           this.logPass = logPass;
           this.logUrl = logUrl;
    }


    /**
     * Gets the logName value for this LonginInfo.
     * 
     * @return logName
     */
    public java.lang.String getLogName() {
        return logName;
    }


    /**
     * Sets the logName value for this LonginInfo.
     * 
     * @param logName
     */
    public void setLogName(java.lang.String logName) {
        this.logName = logName;
    }


    /**
     * Gets the logPass value for this LonginInfo.
     * 
     * @return logPass
     */
    public java.lang.String getLogPass() {
        return logPass;
    }


    /**
     * Sets the logPass value for this LonginInfo.
     * 
     * @param logPass
     */
    public void setLogPass(java.lang.String logPass) {
        this.logPass = logPass;
    }


    /**
     * Gets the logUrl value for this LonginInfo.
     * 
     * @return logUrl
     */
    public java.lang.String getLogUrl() {
        return logUrl;
    }


    /**
     * Sets the logUrl value for this LonginInfo.
     * 
     * @param logUrl
     */
    public void setLogUrl(java.lang.String logUrl) {
        this.logUrl = logUrl;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof LonginInfo)) return false;
        LonginInfo other = (LonginInfo) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.logName==null && other.getLogName()==null) || 
             (this.logName!=null &&
              this.logName.equals(other.getLogName()))) &&
            ((this.logPass==null && other.getLogPass()==null) || 
             (this.logPass!=null &&
              this.logPass.equals(other.getLogPass()))) &&
            ((this.logUrl==null && other.getLogUrl()==null) || 
             (this.logUrl!=null &&
              this.logUrl.equals(other.getLogUrl())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        if (getLogName() != null) {
            _hashCode += getLogName().hashCode();
        }
        if (getLogPass() != null) {
            _hashCode += getLogPass().hashCode();
        }
        if (getLogUrl() != null) {
            _hashCode += getLogUrl().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(LonginInfo.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "LonginInfo"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("logName");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "logName"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("logPass");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "logPass"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("logUrl");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "logUrl"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
