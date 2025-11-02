# 数学算法 - 计算几何
class Solution:
    def intersection(self, start1, end1, start2, end2):
        # translate from c++ by doubao
        # 提取线段端点坐标
        x11, y11 = start1[0], start1[1]
        x12, y12 = end1[0], end1[1]
        x21, y21 = start2[0], start2[1]
        x22, y22 = end2[0], end2[1]
        
        # 标记是否为垂直线（x坐标不变），计算斜率k和截距b
        vert1 = False
        vert2 = False
        k1 = b1 = k2 = b2 = 0.0
        
        if x11 == x12:
            vert1 = True
        else:
            k1 = (y11 - y12) / (x11 - x12)  # 斜率
            b1 = y11 - x11 * k1  # 截距（y = kx + b）
        
        if x21 == x22:
            vert2 = True
        else:
            k2 = (y21 - y22) / (x21 - x22)
            b2 = y21 - x21 * k2
        
        # 情况1：两条都是垂直线
        if vert1 and vert2:
            if x11 == x21:  # x坐标相同才可能相交
                # 计算y方向的重叠范围
                min_y1 = min(y11, y12)
                max_y1 = max(y11, y12)
                min_y2 = min(y21, y22)
                max_y2 = max(y21, y22)
                
                # 无重叠
                if min_y1 > max_y2 or max_y1 < min_y2:
                    return []
                # 有重叠，返回重叠部分的起点（y坐标最大的最小值）
                else:
                    return [float(x11), float(max(min_y1, min_y2))]
            else:
                return []
        
        # 情况2：其中一条是垂直线
        elif vert1 or vert2:
            if vert1:
                # 线1是垂直线(x=x11)，求与线2的交点
                x = x11
                y = k2 * x + b2  # 线2的方程：y = k2x + b2
                # 检查交点是否在两条线段上
                if (min(y11, y12) <= y <= max(y11, y12) and
                    min(x21, x22) <= x <= max(x21, x22) and
                    min(y21, y22) <= y <= max(y21, y22)):
                    return [float(x), float(y)]
            else:
                # 线2是垂直线(x=x21)，求与线1的交点
                x = x21
                y = k1 * x + b1  # 线1的方程：y = k1x + b1
                # 检查交点是否在两条线段上
                if (min(y21, y22) <= y <= max(y21, y22) and
                    min(x11, x12) <= x <= max(x11, x12) and
                    min(y11, y12) <= y <= max(y11, y12)):
                    return [float(x), float(y)]
            return []
        
        # 情况3：两条都不是垂直线
        else:
            # 斜率相同（平行）
            if abs(k1 - k2) < 1e-9:  # 浮点数比较，避免精度问题
                # 截距不同，平行不相交
                if abs(b1 - b2) > 1e-9:
                    return []
                # 截距相同，可能重合
                else:
                    # 检查x方向是否有重叠
                    min_x1 = min(x11, x12)
                    max_x1 = max(x11, x12)
                    min_x2 = min(x21, x22)
                    max_x2 = max(x21, x22)
                    
                    # x方向无重叠，不相交
                    if min_x1 > max_x2 or max_x1 < min_x2:
                        return []
                    # x方向有重叠，取所有端点去重后排序，返回第二个点（原逻辑）
                    else:
                        # 收集所有端点，去重后排序
                        points = {(x11, y11), (x12, y12), (x21, y21), (x22, y22)}
                        sorted_points = sorted(points)  # 按x再y排序
                        return [float(sorted_points[1][0]), float(sorted_points[1][1])]
            # 斜率不同，计算交点
            else:
                x = (b2 - b1) / (k1 - k2)
                y = k1 * x + b1
                # 检查交点是否在两条线段上（x和y都在范围中）
                if (min(x11, x12) - 1e-9 <= x <= max(x11, x12) + 1e-9 and
                    min(y11, y12) - 1e-9 <= y <= max(y11, y12) + 1e-9 and
                    min(x21, x22) - 1e-9 <= x <= max(x21, x22) + 1e-9 and
                    min(y21, y22) - 1e-9 <= y <= max(y21, y22) + 1e-9):
                    return [float(x), float(y)]
                return []