#pragma once
#include <Standard_Handle.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Line.hxx>
#include <Geom_Ellipse.hxx>

using namespace System;
using namespace Xbim::Common::Geometry;

namespace Xbim
{
	namespace Geometry
	{				
		public ref class XbimGeometryParser:IXbimGeometryParser
		{
		public:
			virtual XbimCurveData^ Parse(IXbimCurve^ xbimCurve);
			XbimCurveData^ ParseCircle(Handle_Geom_Circle circle);
			virtual XbimCurveData^ Parse(IXbimEdge^ xbimEdge);
			void Parse(IXbimSolid^ xbimSolid);
		};
	}
}

