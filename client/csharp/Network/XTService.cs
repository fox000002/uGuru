using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.ServiceProcess;
using System.Threading;
using System.Configuration;
using System.Reflection;
using System.IO;
using System.Globalization;
using System.Configuration.Install;

namespace huys
{
    public enum LogLevel
    {
        Warning = -2,
        Allways = -1,
        Error = 0,
        Debug1 = 1,
        Debug2 = 2,
        Debug3 = 3,
        Debug4 = 4,
        Debug5 = 5,
        Debug6 = 6,
        Debug7 = 7,
        Debug8 = 8,
        Debug9 = 9,
    }

    /// <summary>
    /// Tcp Service.
    /// </summary>
    class XTService : ServiceBase
    {
        static string sServiceName = "XTService";
        static string sServiceDisplayName = "Hu's NTService";
        static string sServiceDescription = "XTService to use has template for Windows Services";

        //private EventLog eventLog;
        //private Thread ctThread;

        public XTService()
        {
            this.ServiceName = sServiceName;
            this.EventLog.Log = sServiceName;

            // These Flags set whether or not to handle that specific
            //  type of event. Set to true if you need it, false otherwise.
            this.CanHandlePowerEvent = false;
            this.CanHandleSessionChangeEvent = false;
            this.CanPauseAndContinue = false;
            this.CanShutdown = true;
            this.CanStop = true;
        }


        private static string PrintVersion(string AssemblyName, Type type)
        {
            return AssemblyName.PadRight(60) + " V:"
                + FileVersionInfo.GetVersionInfo(Assembly.GetAssembly(type).Location).FileVersion.ToString();
        }

        public static void WriteOnFile(string sMsg)
        {
            string sFile = ConfigurationManager.AppSettings["LOGPATH"].ToString();
            if (!Directory.Exists(sFile))
            {
                Directory.CreateDirectory(sFile);
            }
            sFile = String.Format(@"{0}\\{1}.{2}.log", sFile, sServiceName, DateTime.Now.ToString("dd-MM-yyyy"));
            StreamWriter sw = new StreamWriter(sFile, true, Encoding.Default);
            sw.WriteLine(sMsg);
            sw.Flush();
            sw.Close();
        }

        public static string ProcessException(Exception ex)
        {
            if (ex == null) return "";

            string message = "\r\n----------------------------------- EXCEPTION: --------------------------------\r\n";
            message += ex.Message;

            message += "\r\n---------------------------------- STACK TRACE: -------------------------------";
            message += ex.StackTrace.ToString();
            message = message.Replace("at ", "\r\nat ");
            message = message.Replace(" in ", "\r\nin ");

            //message += ProcessException(ex.InnerException);

            return message;
        }

        public static void Log(LogLevel level, string sMsg, Exception ex, bool raw)
        {
            {
                lock (typeof(XTService))
                {
                    int logLevel = Convert.ToInt32(ConfigurationManager.AppSettings["LOGTYPE"]);

                    if ((int)level <= logLevel)
                    {
                        string sMessage = "";

                        if (raw == false)
                        {
                            if (level == LogLevel.Error)
                            {
                                sMessage += "*******************************************************************************";
                                sMessage += "\r\n";
                            }
                            else
                            {
                                sMessage += "-------------------------------------------------------------------------------";
                                sMessage += "\r\n";
                            }

                            DateTime oDate = DateTime.Now;
                            sMessage += oDate.ToString("dd-MM-yyyy HH:mm:ss.ffff", DateTimeFormatInfo.InvariantInfo) + " => SVR : " + sMsg;

                            sMessage += ProcessException(ex);

                            Console.WriteLine(sMessage);

                            WriteOnFile(sMessage);
                        }
                        else
                        {
                            Console.Write(sMsg);

                            WriteOnFile(sMsg);
                        }
                    }
                }
            }
        }

        public void GO()
        {
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }

        //OnStart(): Put startup code here
        //Start threads, get inital data, etc.
        protected override void OnStart(string[] args)
        {
            base.OnStart(args);
            Log(LogLevel.Allways, "Service Started", null, false);
            GO();
        }

        //OnStop(): Put your stop code here
        //Stop threads, set final data, etc.
        protected override void OnStop()
        {
            //AppThreads.Stop();
            base.OnStop();
        }

        //OnPause: Put your pause code here
        //Pause working threads, etc.
        protected override void OnPause()
        {
            base.OnPause();
        }

        //OnContinue(): Put your continue code here
        //Un-pause working threads, etc.
        protected override void OnContinue()
        {
            base.OnContinue();
        }
        //OnShutdown(): Called when the System is shutting down
        //Put code here when you need special handling
        //of code that deals with a system shutdown, such
        //as saving special data before shutdown.
        protected override void OnShutdown()
        {
            //AppThreads.Stop();
            base.OnShutdown();
        }

        //OnCustomCommand(): If you need to send a command to your
        //service without the need for Remoting or Sockets, use
        //this method to do custom methods.
        //command=Arbitrary Integer between 128 & 256
        protected override void OnCustomCommand(int command)
        {
            //  A custom command can be sent to a service by using this method:
            //#  int command = 128; //Some Arbitrary number between 128 & 256
            //#  ServiceController sc = new ServiceController("NameOfService");
            //#  sc.ExecuteCommand(command);

            base.OnCustomCommand(command);
        }

        //OnPowerEvent(): Useful for detecting power status changes,
        //such as going into Suspend mode or Low Battery for laptops.
        //powerStatus = The Power Broadcast Status (BatteryLow, Suspend, etc.)
        protected override bool OnPowerEvent(PowerBroadcastStatus powerStatus)
        {
            return base.OnPowerEvent(powerStatus);
        }

        //OnSessionChange(): To handle a change event
        //from a Terminal Server session.
        //Useful if you need to determine
        //when a user logs in remotely or logs off,
        //or when someone logs into the console.
        //changeDescription = The Session Change Event that occured.
        protected override void OnSessionChange(SessionChangeDescription changeDescription)
        {
            base.OnSessionChange(changeDescription);
        }

        protected void InstallService(XTService srv)
        {
            TransactedInstaller ti = new TransactedInstaller();
            NailGunInstaller mi = new NailGunInstaller(sServiceName, sServiceDisplayName, sServiceDescription);
            ti.Installers.Add(mi);
            string basePath = Assembly.GetExecutingAssembly().Location;
            String path = String.Format("/assemblypath={0}", basePath);
            path += "\" \"-s";
            String[] cmdline = { path };
            InstallContext ctx = new InstallContext(Path.ChangeExtension(basePath, ".InstallLog"), cmdline);
            ti.Context = ctx;
            try
            {
                ti.Install(new Hashtable());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        protected void UninstallService(XTService srv)
        {
            TransactedInstaller ti = new TransactedInstaller();
            NailGunInstaller mi = new NailGunInstaller(XTService.sServiceName,
                XTService.sServiceDisplayName, XTService.sServiceDescription);
            ti.Installers.Add(mi);
            string basePath = Assembly.GetExecutingAssembly().Location;
            String path = String.Format("/assemblypath={0}", basePath);
            String[] cmdline = { path };
            InstallContext ctx = new InstallContext(Path.ChangeExtension(basePath, ".InstallLog"), cmdline);
            ti.Context = ctx;
            try
            {
                base.OnStop();
                ti.Uninstall(null);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }

    public class NailGunInstaller : Installer
    {
        public NailGunInstaller(string sName, string sDisplayName, string sServiceDescription)
        {
            ServiceProcessInstaller serviceProcessInstaller = new ServiceProcessInstaller();
            ServiceInstaller serviceInstaller = new ServiceInstaller();

            //# Service Account Information
            serviceProcessInstaller.Account = ServiceAccount.LocalSystem;
            serviceProcessInstaller.Username = null;
            serviceProcessInstaller.Password = null;

            //# Service Information
            serviceInstaller.DisplayName = sDisplayName;
            serviceInstaller.Description = sServiceDescription;
            serviceInstaller.StartType = ServiceStartMode.Automatic;

            //# This must be identical to the WindowsService.ServiceBase name
            //# set in the constructor of WindowsService.cs
            serviceInstaller.ServiceName = sName;

            this.Installers.Add(serviceProcessInstaller);
            this.Installers.Add(serviceInstaller);
        }
    }
}
