using System;
using System.IO;
using System.Reflection;
using Xbim.Common.Geometry;

namespace Xbim.Geometry.Engine.Interop
{
    public class XbimGeometryParser
    {
        private IXbimGeometryParser Parser { get; set; }

        static XbimGeometryParser()
        {

            // We need to wire in a custom assembly resolver since Xbim.Geometry.Engine is 
            // not located using standard probing rules (due to way we deploy processor specific binaries)
            AppDomain.CurrentDomain.AssemblyResolve += XbimCustomAssemblyResolver.ResolverHandler;
        }

        public XbimGeometryParser()
        {
            // Warn if runtime for Engine is not present, this is not necessary any more as we are net472
            //XbimPrerequisitesValidator.Validate();

            var conventions = new XbimArchitectureConventions();    // understands the process we run under
            string assemblyName = $"{conventions.ModuleName}.dll";// + conventions.Suffix; dropping the use of a suffix
            try
            {
                var ass = Assembly.Load(assemblyName);
                var t = ass.GetType("Xbim.Geometry.XbimGeometryParser");
                var obj = Activator.CreateInstance(t);
                if (obj == null)
                {
                    throw new Exception("Failed to create Geometry Engine");
                }

                Parser = obj as IXbimGeometryParser;
                if (Parser == null)
                {
                    throw new Exception("Failed to cast Geometry Engine to IXbimGeometryEngine");
                }

            }
            catch (Exception e)
            {
                throw new FileLoadException($"Failed to load Xbim.Geometry.Engine{conventions.Suffix}.dll", e);
            }
        }

        public XbimCurveData Parse(IXbimCurve xbimCurve)
        {
            return Parser.Parse(xbimCurve);
        }

        public XbimCurveData Parse(IXbimEdge xbimEdge)
        {
            return Parser.Parse(xbimEdge);
        }
    }
}
