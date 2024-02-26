#include "Sequence/Game/Load.h"
#include "Image.h"
#include "GameLib/Framework.h"
using namespace std;
namespace Sequence {
	namespace Game {
		Load::Load(unique_ptr<State>& state_ptr, unsigned stage_id) :
			mStatePtr(state_ptr),
			mStageId(stage_id),
			mSeq(SeqId::SEQ_LOAD),
			mLoadingImagePtr(new LoadingImage("loading.dds")),
			mCountMSec(1000)
		{
			mStatePtr.reset();
		}
		Load::SeqId Load::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_LOAD:
				mLoadingImagePtr->drawImage(0, 0, LoadingImage::Id::IMG_LOADING);
				if (mCountMSec != 1000 && !mStatePtr) {
					static const map<int, string> stage_data = {
						{0,"stageData.txt"},
						{1,"1.txt"},
						{2,"2.txt"},
						{3,"3.txt"},
						{4,"4.txt"},
						{5,"5.txt"},
						{6,"6.txt"},
						{7,"7.txt"},
						{8,"8.txt"},
						{9,"9.txt"},
					};
					ifstream ifs(stage_data.at(mStageId), ifstream::binary);
					ifs.seekg(0, ifstream::end);
					int file_size = static_cast<int>(ifs.tellg());
					ifs.seekg(0, ifstream::beg);
					unique_ptr<char[]> buff(new char[file_size]);
					ifs.read(buff.get(), file_size);

					mStatePtr.reset(new State(buff.get(), file_size));
				}
				mCountMSec -= min(mCountMSec, (unsigned)GameLib::Framework::instance().previousFrameInterval());
				if (!mStatePtr) mCountMSec = max(mCountMSec, 1u);
				if (mCountMSec == 0)next = SeqId::SEQ_END;
				break;
			default:
				break;
			}

			return mSeq = next;
		}
	}
}