/**
 * JobAtt.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.4 Apr 22, 2006 (06:55:48 PDT) WSDL2Java emitter.
 */

package nyapc.crawler.dao;

public class JobAtt  implements java.io.Serializable {
    private java.lang.String category;

    private java.lang.String comment;

    private java.lang.String createTime;

    private java.lang.String dredb;

    private int id;

    private int interval;

    private java.lang.String jobStat;

    private java.lang.String name;

    private java.lang.String seed;

    private java.lang.String seedType;

    private java.lang.String updateFlag;

    private java.lang.String updateTime;

    public JobAtt() {
    }

    public JobAtt(
           java.lang.String category,
           java.lang.String comment,
           java.lang.String createTime,
           java.lang.String dredb,
           int id,
           int interval,
           java.lang.String jobStat,
           java.lang.String name,
           java.lang.String seed,
           java.lang.String seedType,
           java.lang.String updateFlag,
           java.lang.String updateTime) {
           this.category = category;
           this.comment = comment;
           this.createTime = createTime;
           this.dredb = dredb;
           this.id = id;
           this.interval = interval;
           this.jobStat = jobStat;
           this.name = name;
           this.seed = seed;
           this.seedType = seedType;
           this.updateFlag = updateFlag;
           this.updateTime = updateTime;
    }


    /**
     * Gets the category value for this JobAtt.
     * 
     * @return category
     */
    public java.lang.String getCategory() {
        return category;
    }


    /**
     * Sets the category value for this JobAtt.
     * 
     * @param category
     */
    public void setCategory(java.lang.String category) {
        this.category = category;
    }


    /**
     * Gets the comment value for this JobAtt.
     * 
     * @return comment
     */
    public java.lang.String getComment() {
        return comment;
    }


    /**
     * Sets the comment value for this JobAtt.
     * 
     * @param comment
     */
    public void setComment(java.lang.String comment) {
        this.comment = comment;
    }


    /**
     * Gets the createTime value for this JobAtt.
     * 
     * @return createTime
     */
    public java.lang.String getCreateTime() {
        return createTime;
    }


    /**
     * Sets the createTime value for this JobAtt.
     * 
     * @param createTime
     */
    public void setCreateTime(java.lang.String createTime) {
        this.createTime = createTime;
    }


    /**
     * Gets the dredb value for this JobAtt.
     * 
     * @return dredb
     */
    public java.lang.String getDredb() {
        return dredb;
    }


    /**
     * Sets the dredb value for this JobAtt.
     * 
     * @param dredb
     */
    public void setDredb(java.lang.String dredb) {
        this.dredb = dredb;
    }


    /**
     * Gets the id value for this JobAtt.
     * 
     * @return id
     */
    public int getId() {
        return id;
    }


    /**
     * Sets the id value for this JobAtt.
     * 
     * @param id
     */
    public void setId(int id) {
        this.id = id;
    }


    /**
     * Gets the interval value for this JobAtt.
     * 
     * @return interval
     */
    public int getInterval() {
        return interval;
    }


    /**
     * Sets the interval value for this JobAtt.
     * 
     * @param interval
     */
    public void setInterval(int interval) {
        this.interval = interval;
    }


    /**
     * Gets the jobStat value for this JobAtt.
     * 
     * @return jobStat
     */
    public java.lang.String getJobStat() {
        return jobStat;
    }


    /**
     * Sets the jobStat value for this JobAtt.
     * 
     * @param jobStat
     */
    public void setJobStat(java.lang.String jobStat) {
        this.jobStat = jobStat;
    }


    /**
     * Gets the name value for this JobAtt.
     * 
     * @return name
     */
    public java.lang.String getName() {
        return name;
    }


    /**
     * Sets the name value for this JobAtt.
     * 
     * @param name
     */
    public void setName(java.lang.String name) {
        this.name = name;
    }


    /**
     * Gets the seed value for this JobAtt.
     * 
     * @return seed
     */
    public java.lang.String getSeed() {
        return seed;
    }


    /**
     * Sets the seed value for this JobAtt.
     * 
     * @param seed
     */
    public void setSeed(java.lang.String seed) {
        this.seed = seed;
    }


    /**
     * Gets the seedType value for this JobAtt.
     * 
     * @return seedType
     */
    public java.lang.String getSeedType() {
        return seedType;
    }


    /**
     * Sets the seedType value for this JobAtt.
     * 
     * @param seedType
     */
    public void setSeedType(java.lang.String seedType) {
        this.seedType = seedType;
    }


    /**
     * Gets the updateFlag value for this JobAtt.
     * 
     * @return updateFlag
     */
    public java.lang.String getUpdateFlag() {
        return updateFlag;
    }


    /**
     * Sets the updateFlag value for this JobAtt.
     * 
     * @param updateFlag
     */
    public void setUpdateFlag(java.lang.String updateFlag) {
        this.updateFlag = updateFlag;
    }


    /**
     * Gets the updateTime value for this JobAtt.
     * 
     * @return updateTime
     */
    public java.lang.String getUpdateTime() {
        return updateTime;
    }


    /**
     * Sets the updateTime value for this JobAtt.
     * 
     * @param updateTime
     */
    public void setUpdateTime(java.lang.String updateTime) {
        this.updateTime = updateTime;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof JobAtt)) return false;
        JobAtt other = (JobAtt) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.category==null && other.getCategory()==null) || 
             (this.category!=null &&
              this.category.equals(other.getCategory()))) &&
            ((this.comment==null && other.getComment()==null) || 
             (this.comment!=null &&
              this.comment.equals(other.getComment()))) &&
            ((this.createTime==null && other.getCreateTime()==null) || 
             (this.createTime!=null &&
              this.createTime.equals(other.getCreateTime()))) &&
            ((this.dredb==null && other.getDredb()==null) || 
             (this.dredb!=null &&
              this.dredb.equals(other.getDredb()))) &&
            this.id == other.getId() &&
            this.interval == other.getInterval() &&
            ((this.jobStat==null && other.getJobStat()==null) || 
             (this.jobStat!=null &&
              this.jobStat.equals(other.getJobStat()))) &&
            ((this.name==null && other.getName()==null) || 
             (this.name!=null &&
              this.name.equals(other.getName()))) &&
            ((this.seed==null && other.getSeed()==null) || 
             (this.seed!=null &&
              this.seed.equals(other.getSeed()))) &&
            ((this.seedType==null && other.getSeedType()==null) || 
             (this.seedType!=null &&
              this.seedType.equals(other.getSeedType()))) &&
            ((this.updateFlag==null && other.getUpdateFlag()==null) || 
             (this.updateFlag!=null &&
              this.updateFlag.equals(other.getUpdateFlag()))) &&
            ((this.updateTime==null && other.getUpdateTime()==null) || 
             (this.updateTime!=null &&
              this.updateTime.equals(other.getUpdateTime())));
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
        if (getCategory() != null) {
            _hashCode += getCategory().hashCode();
        }
        if (getComment() != null) {
            _hashCode += getComment().hashCode();
        }
        if (getCreateTime() != null) {
            _hashCode += getCreateTime().hashCode();
        }
        if (getDredb() != null) {
            _hashCode += getDredb().hashCode();
        }
        _hashCode += getId();
        _hashCode += getInterval();
        if (getJobStat() != null) {
            _hashCode += getJobStat().hashCode();
        }
        if (getName() != null) {
            _hashCode += getName().hashCode();
        }
        if (getSeed() != null) {
            _hashCode += getSeed().hashCode();
        }
        if (getSeedType() != null) {
            _hashCode += getSeedType().hashCode();
        }
        if (getUpdateFlag() != null) {
            _hashCode += getUpdateFlag().hashCode();
        }
        if (getUpdateTime() != null) {
            _hashCode += getUpdateTime().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(JobAtt.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "JobAtt"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("category");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "category"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("comment");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "comment"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("createTime");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "createTime"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("dredb");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "dredb"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("id");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "id"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        elemField.setNillable(false);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("interval");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "interval"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        elemField.setNillable(false);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("jobStat");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "jobStat"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("name");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "name"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("seed");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "seed"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("seedType");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "seedType"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("updateFlag");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "updateFlag"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("updateTime");
        elemField.setXmlName(new javax.xml.namespace.QName("http://dao.crawler.nyapc", "updateTime"));
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
