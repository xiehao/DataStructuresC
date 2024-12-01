#include <gtest/gtest.h>
#include "dsa/linked_list.h"

TEST(LinkedListTest, CreateAndDestroy) {
    LinkedList* list = linked_list_create();
    ASSERT_TRUE(list != NULL);
    ASSERT_EQ(linked_list_size(list), 0);
    linked_list_destroy(list);
} 