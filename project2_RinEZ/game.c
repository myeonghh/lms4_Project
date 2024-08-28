for (y = 0; y < ylen; y++)
    {
        for (x = 0; x < xlen; x++)
        {
            d_check = 0;
            for (i = 0; i < 50; i++)
            {
                if (skip_chk_arr[i][0] == -1)
                    break;

                if (y == skip_chk_arr[i][0] && x == skip_chk_arr[i][1])
                {
                    d_check = 1;
                    break;
                }
            }
            if (d_check == 1)
            {
                continue;
            }

            if (map[*p_loc][y][x] >= -14 && map[*p_loc][y][x] <= -10)
            {              
                mon = map[*p_loc][y][x];
                left_m_chk = 0;
                right_m_chk = 0;
                up_m_chk = 0;
                down_m_chk = 0;
                move_ran = 0;
                srand(time(NULL));
                
                y_min = ((y-3) < 0)? 0 : y-3;
                x_min = ((x-3) < 0)? 0 : x-3;
                y_max = ((y+3) > 49)? 49 : y+3;
                x_max = ((x+3) > 49)? 49 : x+3;

                int find = 0;
                for (yy = y_min; yy <= y_max; yy++)
                {
                    for (xx = x_min; xx <= x_max; xx++)
                    {
                        if (yy == *p_y && xx == *p_x)
                        {                            
                            find = 1;                            
                            break;
                        }
                    }
                    if (find == 1)
                        break;
                }            
                if (find == 0)
                {
                    
                    continue;
                }
                                  
                if ((*p_y - y) < 0 && *p_x == x) // 상
                {
                    up_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        continue;
                }
                else if ((*p_y - y) < 0 && (*p_x - x) > 0) // 우상
                {
                    if ((*p_y - y) + (*p_x - x) < 0) // 우상좌
                    {
                        move = up_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        if (move == 1) 
                            continue;
                        right_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                            continue;                        
                    }
                    else if ((*p_y - y) + (*p_x - x) == 0) // 우상중
                    {                      
                        while (1)
                        {
                            move_ran = rand() % 2;
                            if (move_ran == 0)
                            {
                                move = up_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                                if (move == 1) 
                                    break;
                                up_m_chk = 1;
                            }
                            else
                            {
                                move = right_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                                if (move == 1) 
                                    break;
                                right_m_chk = 1;
                            }
                            if (up_m_chk == 1 && right_m_chk == 1)
                                break;
                        }
                        continue;
                    }
                    else // 우상우
                    {
                        move = right_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        if (move == 1) 
                            continue;
                        up_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                            continue;
                    }

                }
                else if (*p_y == y && (*p_x - x) > 0)  // 우
                {
                    right_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        continue;
                }
                else if ((*p_y - y) > 0 && (*p_x - x) > 0) // 우하
                {
                    if ((*p_y - y) - (*p_x - x) > 0) //우하우
                    {
                        move = right_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        if (move == 1) 
                            continue;
                        down_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &cnt, skip_chk_arr, &q_cnt);
                            continue;
                    }
                    else if ((*p_y - y) - (*p_x - x) == 0) // 우하중
                    {
                        while (1)
                        {
                            move_ran = rand() % 2;
                            if (move_ran == 0)
                            {
                                move = right_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                                if (move == 1) 
                                    break;
                                right_m_chk = 1;
                            }
                            else
                            {
                                move = down_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &cnt, skip_chk_arr, &q_cnt);
                                if (move == 1) 
                                    break;
                                down_m_chk = 1;
                            }
                            if (right_m_chk == 1 && down_m_chk == 1)
                                break;
                        }
                        continue;
                    }
                    else // 우하좌
                    {
                        move = down_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &cnt, skip_chk_arr, &q_cnt);
                        if (move == 1) 
                            continue;
                        right_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                            continue;
                    }
                    
                }
                else if ((*p_y - y) > 0 && *p_x == x) // 하
                {
                    down_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &cnt, skip_chk_arr, &q_cnt);
                        continue;
                }
                else if ((*p_y - y) > 0 && (*p_x - x) < 0) // 좌하
                {
                    if ((*p_y - y) + (*p_x - x) > 0) // 좌하우
                    {
                        move = down_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &cnt, skip_chk_arr, &q_cnt);
                        if (move == 1) 
                            continue;
                        left_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                            continue;
                    }
                    else if ((*p_y - y) + (*p_x - x) == 0) // 좌하중
                    {
                        while (1)
                        {
                            move_ran = rand() % 2;
                            if (move_ran == 0)
                            {
                                move = down_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &cnt, skip_chk_arr, &q_cnt);
                                if (move == 1) 
                                    break;
                                down_m_chk = 1;
                            }
                            else
                            {
                                move = left_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                                if (move == 1) 
                                    break;
                                left_m_chk = 1;
                            }
                            if (down_m_chk == 1 && left_m_chk == 1)
                                break;
                        }
                        continue;
                    }
                    else // 좌하좌
                    {
                        move = left_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        if (move == 1) 
                            continue;
                        down_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &cnt, skip_chk_arr, &q_cnt);
                            continue;
                    }
                }
                else if (*p_y == y && (*p_x - x) < 0) // 좌
                {
                    left_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        continue;
                }
                else if ((*p_y - y) < 0 && (*p_x - x) < 0) // 좌상
                {
                    if ((*p_y - y) - (*p_x - x) > 0) // 좌상좌
                    {
                        move = left_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        if (move == 1) 
                            continue;
                        up_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                            continue;
                    }
                    else if ((*p_y - y) - (*p_x - x) == 0) // 좌상중
                    {
                        while (1)
                        {
                            move_ran = rand() % 2;
                            if (move_ran == 0)
                            {
                                move = left_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                                if (move == 1) 
                                    break;
                                left_m_chk = 1;
                            }
                            else
                            {
                                move = up_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                                if (move == 1) 
                                    break;
                                up_m_chk = 1;
                            }
                            if (left_m_chk == 1 && up_m_chk == 1)
                                break;
                        }
                        continue;
                    }
                    else // 좌상우
                    {
                        move = up_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                        if (move == 1) 
                            continue;
                        left_move(map, xlen, ylen, zlen, p_x, p_y, p_loc, qmyx, &x, &y,  &mon, &move_chk, &q_cnt);
                            continue;
                    }                
                }
            }
        }
    }