using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Net;

namespace huys
{
    /// <summary>
    /// File transfer stuff.
    /// </summary>
    public class XTTransfer
    {
        /// <summary>
        /// Used to convert strings to byte arrays.
        /// </summary>
        private System.Text.UTF8Encoding encoding=new System.Text.UTF8Encoding();


        /// <summary>
        /// This method downloads the specified URL into a C#
        /// String. This is a very simple method, that you can
        /// reused anytime you need to quickly grab all data 
        /// from a specific URL.
        /// </summary>
        /// <param name="url">The URL to download.</param>
        /// <param name="filename">The filename to download.</param>
        /// <returns>The contents of the URL that was downloaded.</returns>
        public void DownloadBinaryFile(Uri url, String filename)
        {
            byte[] buffer = new byte[4096];
            FileStream os = new FileStream(filename, FileMode.Create);
            WebRequest http = HttpWebRequest.Create(url);
            HttpWebResponse response = (HttpWebResponse)http.GetResponse();
            Stream stream = response.GetResponseStream();

            int count = 0;
            do
            {
                count = stream.Read(buffer, 0, buffer.Length);
                if (count > 0) os.Write(buffer, 0, count);
            } while (count > 0);

            response.Close();
            stream.Close();
            os.Close();
        }

        /// <summary>
        /// Download the specified text page.
        /// </summary>
        /// <param name="page">The URL to download from.</param>
        /// <param name="filename">The local file to save to.</param>
        public void DownloadTextFile(String page, String filename)
        {
            Uri u = new Uri(page);
            FileStream os = new FileStream(filename, FileMode.Create);
            HttpWebRequest http = (HttpWebRequest)HttpWebRequest.Create(u);
            HttpWebResponse response = (HttpWebResponse)http.GetResponse();
            StreamReader reader = new StreamReader(response.GetResponseStream(), System.Text.Encoding.ASCII);
            StreamWriter writer = new StreamWriter(os, System.Text.Encoding.ASCII);
            http.AllowAutoRedirect = false;
            String line;
            do
            {
                line = reader.ReadLine();
                if (line != null) writer.WriteLine(line);
            } while (line != null);
            reader.Close();
            writer.Close();
            os.Close();
        }


        public void Download(String uri, String fn)
        {
            string remoteUri = uri;
            string fileName = fn;
            string myStringWebResource = null;
            // Create a new WebClient instance.
            WebClient myWebClient = new WebClient();
            // Concatenate the domain with the Web resource filename.
            myStringWebResource = remoteUri + fileName;
            //Console.WriteLine("Downloading File \"{0}\" from \"{1}\" .......\n\n", fileName, myStringWebResource);
            // Download the Web resource and save it into the current filesystem folder.
            myWebClient.DownloadFile(myStringWebResource, fileName);
            //Console.WriteLine("Successfully Downloaded File \"{0}\" from \"{1}\"", fileName, myStringWebResource);
            //Console.WriteLine("\nDownloaded file saved in the following file system folder:\n\t" + Application.StartupPath);
        }

        /// <summary>
        /// Download data from an URI.
        /// </summary>
        /// <param name="uri">Resource URI</param>
        /// <returns>Downloaded data in string format</returns>
        public static string DownloadData(String uri)
        {
            string x = null;
            byte[] myDataBuffer = null;
            
            try
            {
                // Create a new WebClient instance.
                WebClient myWebClient = new WebClient();

                // Download the Web resource and save it into a data buffer.
                myDataBuffer = myWebClient.DownloadData(uri);


                x = Encoding.ASCII.GetString(myDataBuffer);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                x = null;
            }
            finally
            {

            }

            // Return the downloaded data.
            return x;
        }

        public static string ExchangeData(string uri, string sdata)
        {
            string x = null;

            try
            {
                //
                Stream us = null;
                //Stream ds = null;
                
                WebRequest request;
                //WebResponse response;

                byte[] data = Encoding.ASCII.GetBytes(sdata);

                request = WebRequest.Create(uri);
                request.Method = "POST";
                request.ContentType = "application/x-www-form-urlencode";
                request.ContentLength = data.Length;

                us = request.GetRequestStream();

                us.Write(data, 0, data.Length);

                StreamReader sr = new StreamReader(request.GetResponse().GetResponseStream());

                // Download the Web resource and save it into a data buffer.
                x = sr.ReadToEnd();

            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.ToString());
                x = null;
            }

            finally
            {

            }

            return x;
        }
    }
}
