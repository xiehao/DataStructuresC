#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "linked_list.h"

TestSuite(linked_list);

// 测试创建链表
Test(linked_list, create_list) {
    LinkedList* list = create_linked_list();
    cr_assert(list != NULL, "链表创建失败");
    cr_assert(list->head != NULL, "头节点创建失败");
    cr_assert(list->head->next == NULL, "新链表的头节点next应该为NULL");
    destroy_linked_list(list);
}

// 测试添加节点到链表头部
Test(linked_list, add_front) {
    LinkedList* list = create_linked_list();
    int value = 42;
    
    cr_assert(add_front_linked_list(list, &value), "添加节点失败");
    cr_assert_eq(DATAVALUE(int, list->head->next->data), value, "添加的数据不正确");
    
    destroy_linked_list(list);
}

// 测试获取链表长度
Test(linked_list, list_length) {
    LinkedList* list = create_linked_list();
    cr_assert_eq(get_linked_list_length(list), 0, "空链表长度应该为0");
    
    int value1 = 1, value2 = 2, value3 = 3;
    add_front_linked_list(list, &value1);
    cr_assert_eq(get_linked_list_length(list), 1, "添加一个节点后长度应该为1");
    
    add_front_linked_list(list, &value2);
    add_front_linked_list(list, &value3);
    cr_assert_eq(get_linked_list_length(list), 3, "添加三个节点后长度应该为3");
    
    destroy_linked_list(list);
}

// 测试按索引插入
Test(linked_list, insert_by_index) {
    LinkedList* list = create_linked_list();
    int value1 = 1, value2 = 2, value3 = 3;
    
    cr_assert(insert_after_linked_by_index(list, 0, &value1), "在索引0后插入失败");
    cr_assert(insert_after_linked_by_index(list, 0, &value2), "在索引0后插入失败");
    cr_assert(insert_after_linked_by_index(list, 1, &value3), "在索引1后插入失败");
    
    cr_assert_eq(get_linked_list_length(list), 3, "插入三个节点后长度应该为3");
    
    destroy_linked_list(list);
}

// 测试删除头部节点
Test(linked_list, remove_front) {
    LinkedList* list = create_linked_list();
    int value1 = 1, value2 = 2;
    DataType removed_value;
    
    add_front_linked_list(list, &value1);
    add_front_linked_list(list, &value2);
    
    cr_assert(remove_front_linked_list(list, &removed_value), "删除头部节点失败");
    cr_assert_eq(DATAVALUE(int, removed_value), value2, "删除的值不正确");
    cr_assert_eq(get_linked_list_length(list), 1, "删除后长度不正确");
    
    destroy_linked_list(list);
}

// 测试按数据搜索
Test(linked_list, search_by_data) {
    LinkedList* list = create_linked_list();
    int value1 = 1, value2 = 2, value3 = 3;
    
    add_front_linked_list(list, &value1);
    add_front_linked_list(list, &value2);
    add_front_linked_list(list, &value3);
    
    LinkedNode* found = search_linked_by_data(list, &value2, equal_ints);
    cr_assert(found != NULL, "未找到应存在的节点");
    cr_assert_eq(DATAVALUE(int, found->data), value2, "找到的节点数据不正确");
    
    destroy_linked_list(list);
}

// 测试清空链表
Test(linked_list, cleanup) {
    LinkedList* list = create_linked_list();
    int value1 = 1, value2 = 2, value3 = 3;
    
    add_front_linked_list(list, &value1);
    add_front_linked_list(list, &value2);
    add_front_linked_list(list, &value3);
    
    cr_assert(cleanup_linked_list(list), "清空链表失败");
    cr_assert_eq(get_linked_list_length(list), 0, "清空后链表长度应为0");
    
    destroy_linked_list(list);
} 