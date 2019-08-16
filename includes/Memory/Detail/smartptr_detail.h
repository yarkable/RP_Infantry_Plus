//
//  "$Id$"
//
//  Copyright (c)1992-2050, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef INFRA_SMART_PTR_DETAIL_H__
#define INFRA_SMART_PTR_DETAIL_H__


namespace Dahua {
namespace Memory {

////////////////////////////////////////////////////////////////////////////////

namespace Detail {

struct static_cast_tag {};
struct const_cast_tag {};
struct dynamic_cast_tag {};
struct polymorphic_cast_tag {};

} // namespace Detail
} // namespace Memory
} // namespace Dahua

#endif // INFRA_SMART_PTR_DETAIL_H__

