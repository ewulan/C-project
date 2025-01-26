#include <stdlib.h>
#include <../unity/unity.h>
#include <../unity/unity_internals.h>
#include <../src/queue_simple.h>  

void setUp(void) 
{

}

void tearDown(void) 
{

}
//Normal Test Cases
// Test case: queue_construct
void test_queue_construct(void) 
{
    Queue *q = NULL;

    //Input NULL
    q = queue_construct(0);
    TEST_ASSERT_NULL_MESSAGE(q, "queue_construct failed : 0");
    free(q);

    //CInput size QUEUE_MAX_SIZE-1
    q = queue_construct(QUEUE_MAX_SIZE-1);
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_construct failed: QUEUE_MAX_SIZE - 1");
    TEST_ASSERT_TRUE_MESSAGE(queue_is_empty(q), "queue_construct size: QUEUE_MAX_SIZE - 1");
    TEST_ASSERT_NULL_MESSAGE(q->p_front, "queue_construct p_front failed : QUEUE_MAX_SIZE - 1");
    TEST_ASSERT_NULL_MESSAGE(q->p_rear, "queue_construct p_rear failed : QUEUE_MAX_SIZE - 1");
    TEST_ASSERT_EQUAL_MESSAGE(0, q->i_size, "queue_construct size mismatch : QUEUE_MAX_SIZE - 1");
    free(q);

    //Input size QUEUE_MAX_SIZE
    q = queue_construct(QUEUE_MAX_SIZE);
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_construct failed: QUEUE_MAX_SIZE");
    TEST_ASSERT_TRUE_MESSAGE(queue_is_empty(q), "queue_construct size: QUEUE_MAX_SIZE");
    free(q);

    //Input size QUEUE_MAX_SIZE+1
    q = queue_construct(QUEUE_MAX_SIZE+1);
    TEST_ASSERT_NULL_MESSAGE(q, "queue_construct failed : QUEUE_MAX_SIZE+1");
    free(q);

}

// Test case: queue_destruct
void test_queue_destruct(void) 
{
    Queue *q = NULL;
    int result = 0; 

    //Input NULL
    result = queue_destruct(q);
    TEST_ASSERT_NULL_MESSAGE(q, "queue_destruct failed : Null");
    TEST_ASSERT_EQUAL_MESSAGE(FAILURE, result, "queue_destruct return failed : Null");
    
    //Input empty queue
    q = queue_construct(1);
    result = queue_destruct(q);
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_destruct return failed : 0");

    //Input non empty queue
    q = queue_construct(QUEUE_MAX_SIZE);
    result = queue_push(q, 1);
    result = queue_destruct(q);
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_destruct return failed : 00");

}


// Test case: queue_is_empty
void test_queue_is_empty(void) 
{
    Queue *q = NULL;
    int result = 0;   

    //Input NULL
    result = queue_is_empty(q);
    TEST_ASSERT_EQUAL_MESSAGE(FAILURE, result, "queue_is_empty return failed : Null");
    
    //Input empty queue
    q = queue_construct(1);
    result = queue_is_empty(q);
    TEST_ASSERT_EQUAL_MESSAGE(1, result, "queue_is_empty return failed : 1");
    
    //Input non empty queue
    result = queue_push(q, 1);
    result = queue_is_empty(q);
    TEST_ASSERT_EQUAL_MESSAGE(0, result, "queue_is_empty return failed : 0");

    result = queue_destruct(q);
    
}


// Test case: queue_is_full
void test_queue_is_full(void) 
{
    Queue *q = NULL;
    int result = 0;   

    //Input NULL
    result = queue_is_full(q);
    TEST_ASSERT_EQUAL_MESSAGE(FAILURE, result, "queue_is_full return failed : Null");
    
    //Input empty queue
    q = queue_construct(1);
    result = queue_is_full(q);
    TEST_ASSERT_EQUAL_MESSAGE(0, result, "queue_is_full return failed : 0");

    //Input non empty && full queue
    result = queue_push(q, 1);
    result = queue_is_full(q);
    TEST_ASSERT_EQUAL_MESSAGE(1, result, "queue_is_full return failed : 1");

    result = queue_destruct(q);
    
}


// Test case: queue_push

void test_queue_push(void) 
{
    Queue *q = NULL;
    int result = 0;   

    //Input NULL
    result = queue_push(q, 1);
    TEST_ASSERT_NULL_MESSAGE(q, "queue_push failed : Null");
    TEST_ASSERT_EQUAL_MESSAGE(FAILURE, result, "queue_push return failed : Null");

    //Input empty queue
    q = queue_construct(1);
    result = queue_push(q, 1);
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_push failed: 0");
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_push return failed : 0");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_front, "queue_push front pointer is NULL : 0");
    TEST_ASSERT_EQUAL_MESSAGE(1, q->p_front->t_data, "queue_push result failed : 0");
    TEST_ASSERT_EQUAL_MESSAGE(1, q->i_size, "queue_push size mismatch : 0");
    TEST_ASSERT_EQUAL_MESSAGE(q->p_front, q->p_rear, "queue_push rear mismatch : 0");

    //Input non empty queue && over size
    result = queue_push(q, 2);
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_push failed: 1");
    TEST_ASSERT_EQUAL_MESSAGE(FAILURE, result, "queue_push return failed : 1");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_front, "queue_push front pointer is NULL : 1");
    TEST_ASSERT_EQUAL_MESSAGE(1, q->p_front->t_data, "queue_push result failed : 1");
    TEST_ASSERT_EQUAL_MESSAGE(1, q->i_size, "queue_push size mismatch : 1");
    TEST_ASSERT_EQUAL_MESSAGE(q->p_front, q->p_rear, "queue_push rear mismatch : 1");

    result = queue_destruct(q);
}

// Test case: queue_pop

void test_queue_pop(void) 
{
    Queue *q = NULL;
    int result = 0; 
    ElementType t_item = 0;

    //Input NULL
    result = queue_pop(q, &t_item);
    TEST_ASSERT_NULL_MESSAGE(q, "queue_pop failed : Null");
    TEST_ASSERT_EQUAL_MESSAGE(FAILURE, result, "queue_pop return failed : Null");

    //Input empty queue
    q = queue_construct(1);
    result = queue_pop(q, &t_item);
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_pop failed: 1");
    TEST_ASSERT_EQUAL_MESSAGE(FAILURE, result, "queue_pop return failed : 1");
    TEST_ASSERT_EQUAL_MESSAGE(0, t_item, "queue_pop result failed : 1");
    TEST_ASSERT_NULL_MESSAGE(q->p_front, "queue_pop p_front failed : 1");
    TEST_ASSERT_NULL_MESSAGE(q->p_rear, "queue_pop p_rear failed : 1");
    TEST_ASSERT_EQUAL_MESSAGE(0, q->i_size, "queue_pop size mismatch : 1");

    //Input non empty && full queue 
    q = queue_construct(1);
    result = queue_push(q, 1);
    result = queue_pop(q, &t_item);
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_pop failed: 0");
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_pop return failed : 0");
    TEST_ASSERT_EQUAL_MESSAGE(1, t_item, "queue_pop result failed : 0");
    TEST_ASSERT_NULL_MESSAGE(q->p_front, "queue_pop p_front failed : 0");
    TEST_ASSERT_NULL_MESSAGE(q->p_rear, "queue_pop p_rear failed : 0");
    TEST_ASSERT_EQUAL_MESSAGE(0, q->i_size, "queue_pop size mismatch : 0");

    result = queue_destruct(q);
}

//Test case: normal test
void test_queue_normal(void) 
{
    Queue *q = NULL;
    int result = 0; 
    ElementType t_item = 0;

    q = queue_construct(3);

    result = queue_push(q, 1);
    result = queue_push(q, 2);
    result = queue_push(q, 3);

    //1->2->3
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_normal failed: 0");
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_normal return failed : 0");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_front, "queue_normal front pointer is NULL : 0");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_rear, "queue_normal front pointer is NULL : 0");
    TEST_ASSERT_EQUAL_MESSAGE(1, q->p_front->t_data, "queue_normal result failed : 0");
    TEST_ASSERT_EQUAL_MESSAGE(3, q->i_size, "queue_normal size mismatch : 0");
    TEST_ASSERT_EQUAL_MESSAGE(3, q->p_rear->t_data, "queue_normal rear mismatch : 0");

    result = queue_pop(q, &t_item);
    //2->3
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_normal failed: 01");
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_normal return failed : 01");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_front, "queue_normal front pointer is NULL : 01");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_rear, "queue_normal front pointer is NULL : 01");
    TEST_ASSERT_EQUAL_MESSAGE(2, q->p_front->t_data, "queue_normal result failed : 01");
    TEST_ASSERT_EQUAL_MESSAGE(2, q->i_size, "queue_normal size mismatch : 1");
    TEST_ASSERT_EQUAL_MESSAGE(3, q->p_rear->t_data, "queue_normal rear mismatch : 01");

    result = queue_push(q, 4);
    //2->3->4
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_normal failed: 02");
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_normal return failed : 02");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_front, "queue_normal front pointer is NULL : 02");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_rear, "queue_normal front pointer is NULL : 02");
    TEST_ASSERT_EQUAL_MESSAGE(2, q->p_front->t_data, "queue_normal result failed : 02");
    TEST_ASSERT_EQUAL_MESSAGE(3, q->i_size, "queue_normal size mismatch : 2");
    TEST_ASSERT_EQUAL_MESSAGE(4, q->p_rear->t_data, "queue_normal rear mismatch : 02");

    result = queue_pop(q, &t_item);
    result = queue_pop(q, &t_item);
    //4
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_normal failed: 3");
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_normal return failed : 03");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_front, "queue_normal front pointer is NULL : 03");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_rear, "queue_normal front pointer is NULL : 03");
    TEST_ASSERT_EQUAL_MESSAGE(4, q->p_front->t_data, "queue_normal result failed : 03");
    TEST_ASSERT_EQUAL_MESSAGE(1, q->i_size, "queue_normal size mismatch : 03");
    TEST_ASSERT_EQUAL_MESSAGE(4, q->p_rear->t_data, "queue_normal rear mismatch : 03");

    result = queue_push(q, 5);
    result = queue_push(q, 6);
    //4->5->6
    TEST_ASSERT_NOT_NULL_MESSAGE(q, "queue_normal failed: 04");
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_normal return failed : 04");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_front, "queue_normal front pointer is NULL : 04");
    TEST_ASSERT_NOT_NULL_MESSAGE(q->p_rear, "queue_normal front pointer is NULL : 04");
    TEST_ASSERT_EQUAL_MESSAGE(4, q->p_front->t_data, "queue_normal result failed : 04");
    TEST_ASSERT_EQUAL_MESSAGE(3, q->i_size, "queue_normal size mismatch : 04");
    TEST_ASSERT_EQUAL_MESSAGE(6, q->p_rear->t_data, "queue_normal rear mismatch : 04");

    
    result = queue_destruct(q);
    TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "queue_normal queue_destruct return failed : 0");
    
}

// Main function to run all tests
int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(test_queue_construct);
    RUN_TEST(test_queue_destruct);
    RUN_TEST(test_queue_is_empty);
    RUN_TEST(test_queue_is_full);
    RUN_TEST(test_queue_push);
    RUN_TEST(test_queue_pop);
    RUN_TEST(test_queue_normal);
    return UNITY_END();
}