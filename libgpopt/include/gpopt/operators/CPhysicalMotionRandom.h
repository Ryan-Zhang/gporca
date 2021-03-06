//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CPhysicalMotionRandom.h
//
//	@doc:
//		Physical Random motion operator
//---------------------------------------------------------------------------
#ifndef GPOPT_CPhysicalMotionRandom_H
#define GPOPT_CPhysicalMotionRandom_H

#include "gpos/base.h"

#include "gpopt/base/COrderSpec.h"
#include "gpopt/base/CDistributionSpecRandom.h"
#include "gpopt/operators/CPhysicalMotion.h"

namespace gpopt
{
	
	//---------------------------------------------------------------------------
	//	@class:
	//		CPhysicalMotionRandom
	//
	//	@doc:
	//		Random motion operator
	//
	//---------------------------------------------------------------------------
	class CPhysicalMotionRandom : public CPhysicalMotion
	{

		private:					

			// distribution spec
			CDistributionSpecRandom *m_pdsRandom;
		
			// private copy ctor
			CPhysicalMotionRandom(const CPhysicalMotionRandom &);

		public:
		
			// ctor
			CPhysicalMotionRandom
				(
				IMemoryPool *mp, 
				CDistributionSpecRandom *pdsRandom
				);
			
			// dtor
			virtual 
			~CPhysicalMotionRandom();

			// ident accessors
			virtual 
			EOperatorId Eopid() const
			{
				return EopPhysicalMotionRandom;
			}
			
			virtual 
			const CHAR *SzId() const
			{
				return "CPhysicalMotionRandom";
			}
			
			// output distribution accessor
			virtual
			CDistributionSpec *Pds() const
			{
				return m_pdsRandom;
			}

			// is distribution duplicate sensitive
			BOOL IsDuplicateSensitive() const
			{
				return m_pdsRandom->IsDuplicateSensitive();
			}
			
			// match function
			virtual
			BOOL Matches(COperator *pop) const;

			//-------------------------------------------------------------------------------------
			// Required Plan Properties
			//-------------------------------------------------------------------------------------

			// compute required output columns of the n-th child
			virtual
			CColRefSet *PcrsRequired
				(
				IMemoryPool *mp,
				CExpressionHandle &exprhdl,
				CColRefSet *pcrsInput,
				ULONG child_index,
				CDrvdProp2dArray *pdrgpdpCtxt,
				ULONG ulOptReq
				);

			// compute required sort order of the n-th child
			virtual
			COrderSpec *PosRequired
				(
				IMemoryPool *mp,
				CExpressionHandle &exprhdl,
				COrderSpec *posInput,
				ULONG child_index,
				CDrvdProp2dArray *pdrgpdpCtxt,
				ULONG ulOptReq
				)
				const;

			// check if required columns are included in output columns
			virtual
			BOOL FProvidesReqdCols(CExpressionHandle &exprhdl, CColRefSet *pcrsRequired, ULONG ulOptReq) const;
			
			//-------------------------------------------------------------------------------------
			// Derived Plan Properties
			//-------------------------------------------------------------------------------------

			// derive sort order
			virtual
			COrderSpec *PosDerive(IMemoryPool *mp, CExpressionHandle &exprhdl) const;
			
			//-------------------------------------------------------------------------------------
			// Enforced Properties
			//-------------------------------------------------------------------------------------

			// return order property enforcing type for this operator
			virtual
			CEnfdProp::EPropEnforcingType EpetOrder
				(
				CExpressionHandle &exprhdl,
				const CEnfdOrder *peo
				)
				const;

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------

			// print
			virtual 
			IOstream &OsPrint(IOstream &) const;
			
			// conversion function
			static
			CPhysicalMotionRandom *PopConvert(COperator *pop);			
					
	}; // class CPhysicalMotionRandom

}

#endif // !GPOPT_CPhysicalMotionRandom_H

// EOF
