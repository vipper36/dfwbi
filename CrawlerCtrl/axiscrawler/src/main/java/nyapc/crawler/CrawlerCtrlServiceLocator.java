/**
 * CrawlerCtrlServiceLocator.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.4 Apr 22, 2006 (06:55:48 PDT) WSDL2Java emitter.
 */

package nyapc.crawler;

public class CrawlerCtrlServiceLocator extends org.apache.axis.client.Service implements nyapc.crawler.CrawlerCtrlService {

    public CrawlerCtrlServiceLocator() {
    }


    public CrawlerCtrlServiceLocator(org.apache.axis.EngineConfiguration config) {
        super(config);
    }

    public CrawlerCtrlServiceLocator(java.lang.String wsdlLoc, javax.xml.namespace.QName sName) throws javax.xml.rpc.ServiceException {
        super(wsdlLoc, sName);
    }

    // Use to get a proxy class for CrawlerCtrl
    private java.lang.String CrawlerCtrl_address = "http://localhost:8080/WebServiceCrawler/services/CrawlerCtrl";

    public java.lang.String getCrawlerCtrlAddress() {
        return CrawlerCtrl_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String CrawlerCtrlWSDDServiceName = "CrawlerCtrl";

    public java.lang.String getCrawlerCtrlWSDDServiceName() {
        return CrawlerCtrlWSDDServiceName;
    }

    public void setCrawlerCtrlWSDDServiceName(java.lang.String name) {
        CrawlerCtrlWSDDServiceName = name;
    }

    public nyapc.crawler.CrawlerCtrl getCrawlerCtrl() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(CrawlerCtrl_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getCrawlerCtrl(endpoint);
    }

    public nyapc.crawler.CrawlerCtrl getCrawlerCtrl(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            nyapc.crawler.CrawlerCtrlSoapBindingStub _stub = new nyapc.crawler.CrawlerCtrlSoapBindingStub(portAddress, this);
            _stub.setPortName(getCrawlerCtrlWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setCrawlerCtrlEndpointAddress(java.lang.String address) {
        CrawlerCtrl_address = address;
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        try {
            if (nyapc.crawler.CrawlerCtrl.class.isAssignableFrom(serviceEndpointInterface)) {
                nyapc.crawler.CrawlerCtrlSoapBindingStub _stub = new nyapc.crawler.CrawlerCtrlSoapBindingStub(new java.net.URL(CrawlerCtrl_address), this);
                _stub.setPortName(getCrawlerCtrlWSDDServiceName());
                return _stub;
            }
        }
        catch (java.lang.Throwable t) {
            throw new javax.xml.rpc.ServiceException(t);
        }
        throw new javax.xml.rpc.ServiceException("There is no stub implementation for the interface:  " + (serviceEndpointInterface == null ? "null" : serviceEndpointInterface.getName()));
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(javax.xml.namespace.QName portName, Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        if (portName == null) {
            return getPort(serviceEndpointInterface);
        }
        java.lang.String inputPortName = portName.getLocalPart();
        if ("CrawlerCtrl".equals(inputPortName)) {
            return getCrawlerCtrl();
        }
        else  {
            java.rmi.Remote _stub = getPort(serviceEndpointInterface);
            ((org.apache.axis.client.Stub) _stub).setPortName(portName);
            return _stub;
        }
    }

    public javax.xml.namespace.QName getServiceName() {
        return new javax.xml.namespace.QName("http://crawler.nyapc", "CrawlerCtrlService");
    }

    private java.util.HashSet ports = null;

    public java.util.Iterator getPorts() {
        if (ports == null) {
            ports = new java.util.HashSet();
            ports.add(new javax.xml.namespace.QName("http://crawler.nyapc", "CrawlerCtrl"));
        }
        return ports.iterator();
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(java.lang.String portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        
if ("CrawlerCtrl".equals(portName)) {
            setCrawlerCtrlEndpointAddress(address);
        }
        else 
{ // Unknown Port Name
            throw new javax.xml.rpc.ServiceException(" Cannot set Endpoint Address for Unknown Port" + portName);
        }
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(javax.xml.namespace.QName portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        setEndpointAddress(portName.getLocalPart(), address);
    }

}
