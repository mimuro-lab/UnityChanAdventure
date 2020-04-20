#pragma once

//template <typename _T>
// 二分木のノード
struct Node
{
    int    value;     // 値
    Node* pNext[2];  // 子ノード
};

// 二分木
struct Tree
{
    int    value;  // 値
    Node* pRoot;  // ルート
};