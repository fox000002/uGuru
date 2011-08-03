using System;
using System.IO;
using System.Xml;
using System.Xml.XPath;

namespace huys
{
    /// <summary>
    /// Tcp Configuration.
    /// </summary>
    public class XTConfiguration
    {
        /// <summary>
        /// Tcp Configuration.
        /// </summary>
        public XTConfiguration()
        {

        }

        //
        private XPathDocument document = null;
        private XPathNavigator navigator = null;

        //
        public void load(string fn)
        {
            document = new XPathDocument(fn);
            navigator = document.CreateNavigator();
        }

        //
        public void load(Stream stream)
        {
            document = new XPathDocument(stream);
            navigator = document.CreateNavigator();
        }

        /// <summary>
        /// Extract target object with XPathExpression.
        /// </summary>
        public object NavExp(string exp)
        {      
            XPathExpression xpath = XPathExpression.Compile(exp);

            Console.WriteLine("Expression Return {0}", xpath.ReturnType.ToString());

            switch (xpath.ReturnType)
            {
                case XPathResultType.Number:
                    Console.WriteLine(navigator.Evaluate(xpath));
                    break;

                case XPathResultType.NodeSet:
                    XPathNodeIterator nodes = navigator.Select(xpath);
                    while (nodes.MoveNext())
                    {
                        Console.WriteLine(nodes.Current.ToString());
                    }
                    break;

                case XPathResultType.Boolean:
                    if ((bool)navigator.Evaluate(xpath))
                        Console.WriteLine("True!");
                    break;

                case XPathResultType.String:
                    Console.WriteLine(navigator.Evaluate(xpath));
                    break;
            }

            return navigator.Evaluate(xpath);
        }
    }
}
