// pch.h: ����Ԥ�����ͷ�ļ���
// �·��г����ļ�������һ�Σ�����˽������ɵ��������ܡ�
// �⻹��Ӱ�� IntelliSense ���ܣ�����������ɺ�������������ܡ�
// ���ǣ�����˴��г����ļ��е��κ�һ��������֮���и��£�����ȫ�����������±��롣
// �����ڴ˴����ҪƵ�����µ��ļ����⽫ʹ������������Ч��

#ifndef PCH_H
#define PCH_H

// ���Ҫ�ڴ˴�Ԥ����ı�ͷ
#include "framework.h"

// google-test
#include "gtest/gtest.h"

// std
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <numbers>
#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <optional>

// boost
#include <boost/format.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

// hive
#include "common/Product.h"
#include "common/Factory.h"
#include "common/Singleton.h"
#include "common/CommonInterface.h"
#include "common/EventLoggerInterface.h"
#include "common/DesignPatternInterface.h"
#include "common/UtilityInterface.h"
#include "common/MathInterface.h"
#include "common/CpuTimer.h"

// lib
#include "Loader.h"
#include "OBJLoader.h"

#endif //PCH_H
