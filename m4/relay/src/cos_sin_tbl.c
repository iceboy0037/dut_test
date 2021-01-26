const float sin_table_1_fft[24] = {
	0.0,
	0.258819580078125,
	0.500000000000000,
	0.707092285156250,
	0.866027832031250,
	0.965911865234375,
	1.000000000000000,
	0.965911865234375,
	0.866027832031250,
	0.707092285156250,
	0.500000000000000,
	0.258819580078125,
	0.0,
	-0.258819580078125,
	-0.500000000000000,
	-0.707092285156250,
	-0.866027832031250,
	-0.965911865234375,
	-1.000000000000000,
	-0.965911865234375,
	-0.866027832031250,
	-0.707092285156250,
	-0.500000000000000,
	-0.258819580078125
};

const float cos_table_1_fft[24] = {
	1.000000000000000,
	0.965911865234375,
	0.866027832031250,
	0.707092285156250,
	0.500000000000000,
	0.258819580078125,
	0.0,
	-0.258819580078125,
	-0.500000000000000,
	-0.707092285156250,
	-0.866027832031250,
	-0.965911865234375,
	-1.000000000000000,
	-0.965911865234375,
	-0.866027832031250,
	-0.707092285156250,
	-0.500000000000000,
	-0.258819580078125,
	0.0,
	0.258819580078125,
	0.500000000000000,
	0.707092285156250,
	0.866027832031250,
	0.965911865234375
};

const float sin_table_2_fft[24] = {
	0.0,
	0.500000000000000,
	0.866027832031250,
	1.000000000000000,
	0.866027832031250,
	0.500000000000000,
	0.0,
	-0.500000000000000,
	-0.866027832031250,
	-1.000000000000000,
	-0.866027832031250,
	-0.500000000000000,
	0.0,
	0.500000000000000,
	0.866027832031250,
	1.000000000000000,
	0.866027832031250,
	0.500000000000000,
	0.0,
	-0.500000000000000,
	-0.866027832031250,
	-1.000000000000000,
	-0.866027832031250,
	-0.500000000000000
};

const float cos_table_2_fft[24] = {
	1.000000000000000,
	0.866027832031250,
	0.500000000000000,
	0.0,
	-0.500000000000000,
	-0.866027832031250,
	-1.000000000000000,
	-0.866027832031250,
	-0.500000000000000,
	0.0,
	0.500000000000000,
	0.866027832031250,
	1.000000000000000,
	0.866027832031250,
	0.500000000000000,
	0.0,
	-0.500000000000000,
	-0.866027832031250,
	-1.000000000000000,
	-0.866027832031250,
	-0.500000000000000,
	0.0,
	0.500000000000000,
	0.866027832031250
};

const float cos_table_1_yc[96] = {
	1.000000000000000,
	0.997863769531250,
	0.991455078125000,
	0.980773925781250,
	0.965911865234375,
	0.946929931640625,
	0.923889160156250,
	0.896881103515625,
	0.866027832031250,
	0.831481933593750,
	0.793365478515625,
	0.751831054687500,
	0.707092285156250,
	0.659332275390625,
	0.608764648437500,
	0.555572509765625,
	0.500000000000000,
	0.442291259765625,
	0.382690429687500,
	0.321441650390625,
	0.258819580078125,
	0.195098876953125,
	0.130523681640625,
	0.065399169921875,
	0.0,
	-0.065399169921875,
	-0.130523681640625,
	-0.195098876953125,
	-0.258819580078125,
	-0.321441650390625,
	-0.382690429687500,
	-0.442291259765625,
	-0.500000000000000,
	-0.555572509765625,
	-0.608764648437500,
	-0.659332275390625,
	-0.707092285156250,
	-0.751831054687500,
	-0.793365478515625,
	-0.831481933593750,
	-0.866027832031250,
	-0.896881103515625,
	-0.923889160156250,
	-0.946929931640625,
	-0.965911865234375,
	-0.980773925781250,
	-0.991455078125000,
	-0.997863769531250,
	-1.000000000000000,
	-0.997863769531250,
	-0.991455078125000,
	-0.980773925781250,
	-0.965911865234375,
	-0.946929931640625,
	-0.923889160156250,
	-0.896881103515625,
	-0.866027832031250,
	-0.831481933593750,
	-0.793365478515625,
	-0.751831054687500,
	-0.707092285156250,
	-0.659332275390625,
	-0.608764648437500,
	-0.555572509765625,
	-0.500000000000000,
	-0.442291259765625,
	-0.382690429687500,
	-0.321441650390625,
	-0.258819580078125,
	-0.195098876953125,
	-0.130523681640625,
	-0.065399169921875,
	0.0,
	0.065399169921875,
	0.130523681640625,
	0.195098876953125,
	0.258819580078125,
	0.321441650390625,
	0.382690429687500,
	0.442291259765625,
	0.500000000000000,
	0.555572509765625,
	0.608764648437500,
	0.659332275390625,
	0.707092285156250,
	0.751831054687500,
	0.793365478515625,
	0.831481933593750,
	0.866027832031250,
	0.896881103515625,
	0.923889160156250,
	0.946929931640625,
	0.965911865234375,
	0.980773925781250,
	0.991455078125000,
	0.997863769531250
};

const float sin_table_1_yc[96] = {
	0.0,
	0.065399169921875,
	0.130523681640625,
	0.195098876953125,
	0.258819580078125,
	0.321441650390625,
	0.382690429687500,
	0.442291259765625,
	0.500000000000000,
	0.555572509765625,
	0.608764648437500,
	0.659332275390625,
	0.707092285156250,
	0.751831054687500,
	0.793365478515625,
	0.831481933593750,
	0.866027832031250,
	0.896881103515625,
	0.923889160156250,
	0.946929931640625,
	0.965911865234375,
	0.980773925781250,
	0.991455078125000,
	0.997863769531250,
	1.000000000000000,
	0.997863769531250,
	0.991455078125000,
	0.980773925781250,
	0.965911865234375,
	0.946929931640625,
	0.923889160156250,
	0.896881103515625,
	0.866027832031250,
	0.831481933593750,
	0.793365478515625,
	0.751831054687500,
	0.707092285156250,
	0.659332275390625,
	0.608764648437500,
	0.555572509765625,
	0.500000000000000,
	0.442291259765625,
	0.382690429687500,
	0.321441650390625,
	0.258819580078125,
	0.195098876953125,
	0.130523681640625,
	0.065399169921875,
	0.0,
	-0.065399169921875,
	-0.130523681640625,
	-0.195098876953125,
	-0.258819580078125,
	-0.321441650390625,
	-0.382690429687500,
	-0.442291259765625,
	-0.500000000000000,
	-0.555572509765625,
	-0.608764648437500,
	-0.659332275390625,
	-0.707092285156250,
	-0.751831054687500,
	-0.793365478515625,
	-0.831481933593750,
	-0.866027832031250,
	-0.896881103515625,
	-0.923889160156250,
	-0.946929931640625,
	-0.965911865234375,
	-0.980773925781250,
	-0.991455078125000,
	-0.997863769531250,
	-1.000000000000000,
	-0.997863769531250,
	-0.991455078125000,
	-0.980773925781250,
	-0.965911865234375,
	-0.946929931640625,
	-0.923889160156250,
	-0.896881103515625,
	-0.866027832031250,
	-0.831481933593750,
	-0.793365478515625,
	-0.751831054687500,
	-0.707092285156250,
	-0.659332275390625,
	-0.608764648437500,
	-0.555572509765625,
	-0.500000000000000,
	-0.442291259765625,
	-0.382690429687500,
	-0.321441650390625,
	-0.258819580078125,
	-0.195098876953125,
	-0.130523681640625,
	-0.065399169921875
};

