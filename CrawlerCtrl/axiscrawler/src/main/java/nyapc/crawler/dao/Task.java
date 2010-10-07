/**
 * Task.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.4 Apr 22, 2006 (06:55:48 PDT) WSDL2Java emitter.
 */

package nyapc.crawler.dao;

public class Task  implements java.io.Serializable {
    private java.lang.String ids;

    private int job_id;

    private int taskId;

    private java.lang.String type;

    private java.lang.String urls;

    private int wrap_id;

    private int wrap_version;

    public Task() {
    }

    public Task(
           java.lang.String ids,
           int job_id,
           int taskId,
           java.lang.String type,
           java.lang.String urls,
           int wrap_id,
           int wrap_version) {
           this.ids = ids;
           this.job_id = job_id;
           this.taskId = taskId;
           this.type = type;
           this.urls = urls;
           this.wrap_id = wrap_id;
           this.wrap_version = wrap_version;
    }


    /**
     * Gets the ids value for this Task.
     * 
     * @return ids
     */
    public java.lang.String getIds() {
        return ids;
    }


    /**
     * Sets the ids value for this Task.
     * 
     * @param ids
     */
    public void setIds(java.lang.String ids) {
        this.ids = ids;
    }


    /**
     * Gets the job_id value for this Task.
     * 
     * @return job_id
     */
    public int getJob_id() {
        return job_id;
    }


    /**
     * Sets the job_id value for this Task.
     * 
     * @param job_id
     */
    public void setJob_id(int job_id) {
        this.job_id = job_id;
    }


    /**
     * Gets the taskId value for this Task.
     * 
     * @return taskId
     */
    public int getTaskId() {
        return taskId;
    }


    /**
     * Sets the taskId value for this Task.
     * 
     * @param taskId
     */
    public void setTaskId(int taskId) {
        this.taskId = taskId;
    }


    /**
     * Gets the type value for this Task.
     * 
     * @return type
     */
    public java.lang.String getType() {
        return type;
    }


    /**
     * Sets the type value for this Task.
     * 
     * @param type
     */
    public void setType(java.lang.String type) {
        this.type = type;
    }


    /**
     * Gets the urls value for this Task.
     * 
     * @return urls
     */
    public java.lang.String getUrls() {
        return urls;
    }


    /**
     * Sets the urls value for this Task.
     * 
     * @param urls
     */
    public void setUrls(java.lang.String urls) {
        this.urls = urls;
    }


    /**
     * Gets the wrap_id value for this Task.
     * 
     * @return wrap_id
     */
    public int getWrap_id() {
        return wrap_id;
    }


    /**
     * Sets the wrap_id value for this Task.
     * 
     * @param wrap_id
     */
    public void setWrap_id(int wrap_id) {
        this.wrap_id = wrap_id;
    }


    /**
     * Gets the wrap_version value for this Task.
     * 
     * @return wrap_version
     */
    public int getWrap_version() {
        return wrap_version;
    }


    /**
     * Sets the wrap_version value for this Task.
     * 
     * @param wrap_version
     */
    public void setWrap_version(int wrap_version) {
        this.wrap_version = wrap_version;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof Task)) return false;
        Task other = (Task) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.ids==null && other.getIds()==null) || 
             (this.ids!=null &&
              this.ids.equals(other.getIds()))) &&
            this.job_id == other.getJob_id() &&
            this.taskId == other.getTaskId() &&
            ((this.type==null && other.getType()==null) || 
             (this.type!=null &&
              this.type.equals(other.getType()))) &&
            ((this.urls==null && other.getUrls()==null) || 
             (this.urls!=null &&
              this.urls.equals(other.getUrls()))) &&
            this.wrap_id == other.getWrap_id() &&
            this.wrap_version == other.getWrap_version();
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
        if (getIds() != null) {
            _hashCode += getIds().hashCode();
        }
        _hashCode += getJob_id();
        _hashCode += getTaskId();
        if (getType() != null) {
            _hashCode += getType().hashCode();
        }
        if (getUrls() != null) {
            _hashCode += getUrls().hashCode();
        }
        _hashCode += getWrap_id();
        _hashCode += getWrap_version();
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(Task.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "Task"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("ids");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "ids"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("job_id");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "job_id"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        elemField.setNillable(false);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("taskId");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "taskId"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        elemField.setNillable(false);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("type");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "type"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("urls");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "urls"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("wrap_id");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "wrap_id"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        elemField.setNillable(false);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("wrap_version");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "wrap_version"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        elemField.setNillable(false);
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
