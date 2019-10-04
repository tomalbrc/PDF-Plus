//
//  3DView.hpp
//  PDF-Plus-macOS
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef _DView_hpp
#define _DView_hpp

#include <cstdio>
#include "Object.hpp"
#include "ObjectRef.hpp"

namespace PDF_Plus {
	/**
	 3D Render Mode, fixed values for now
	 // TODO: Enum classes
	 */
	class _3DRenderMode : public Object {
	public:
		_3DRenderMode(const std::weak_ptr<Xref>& parent) : Object{parent} {
			_dict[Key::Type] = "/3DRenderMode";
			_dict[Key::Subtype] = "/Solid";
		}
	};
	
	/**
	 3D Lighting Scheme, fixed values for now
	 // TODO: Enum classes
	 */
	class _3DLightingScheme : public Object {
	public:
		_3DLightingScheme(const std::weak_ptr<Xref>& parent) : Object{parent} {
			_dict[Key::Type] = "/3DLightingScheme";
			_dict[Key::Subtype] = "/Headlamp";
		}
	};
	
	/**
	 
	 */
	class _3DView : public Object {
	public:
		_3DView(const std::weak_ptr<Xref>& parent, const MultiVariantArray& position, const MultiVariantArray& rotation) : Object{parent} {
			
			_ls = std::make_shared<_3DLightingScheme>(parent);
			_rm = std::make_shared<_3DRenderMode>(parent);
			
			_dict[Key::Type] = "/3DView";
			_dict["XN"] = String{"Default View"}; // External Name (UI)
			_dict["MS"] = "/M";
			_dict["P"] = "<</Subtype /P /PS /Min /FOV 30.0>>";
			_dict["BG"] = "<</Subtype /SC /C [1.0 0.5 0.5]>>";
			
			std::array<float, 3> p = {position.get<float>(0), position.get<float>(1), position.get<float>(2)};
			std::array<float, 3> u = {rotation.get<float>(0), rotation.get<float>(1), rotation.get<float>(2)};
			std::array<float, 3> u2 = {std::pow(u[0], 2.f), std::pow(u[1], 2.f), std::pow(u[2], 2.f)};
			auto t = rotation.get<float>(3);
			
			_dict["C2W"] = MultiVariantArray{
				cos(t)+u2[0]*(1.f-cos(t)),
				u[0]*u[1]*(1.f-cos(t))-u[2]*sin(t),
				u[0]*u[2]*(1.f-cos(t))*u[1]*sin(t),
				
				u[1]*u[0]*(1.f-cos(t))*u[2]*sin(t),
				cos(t)+u2[1]*(1.f-cos(t)),
				u[1]*u[2]*(1.f-cos(t))*u[0]*sin(t),

				u[2]*u[0]*(1.f-cos(t))*u[1]*sin(t),
				u[2]*u[1]*(1.f-cos(t))*u[0]*sin(t),
				cos(t)+u2[2]*(1.f-cos(t)),

				p[0], p[1], p[2]
			};
			
			_dict["RM"] = ObjectRef{_rm.get()};
			_dict["LS"] = ObjectRef{_ls.get()};
		}
		
	private:
		std::shared_ptr<_3DLightingScheme> _ls;
		std::shared_ptr<_3DRenderMode> _rm;
	};
}

#endif /* _DView_hpp */
