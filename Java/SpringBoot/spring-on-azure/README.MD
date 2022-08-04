# Notes

* The Java JDK MUST be the one of supported by the Azure, right not the highest version is Java 17. 
I had errors caused by the fact that I was compiling using Java 18 with SDK version set to 17 - this is not working.

# Deployment to Azure App Service using azure-webapp-maven-plugin
* Build package `mvn clean package`
* Start plugin that will configure the data required to Azure deployment `mvn com.microsoft.azure:azure-webapp-maven-plugin:2.5.0:config` (be sure to be logged into your Azure and have a subscription).
* Perform deployment `mvn azure-webapp:deploy`
* Go to the Azure and see your service working there.